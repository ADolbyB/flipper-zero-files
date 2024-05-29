#!/bin/sh

application_name="flipp_pomodoro"
repo_root=$(dirname $0)/..

mkdir -p ${repo_root}/dist

# Fetch all firmwares submodules
git submodule update --init --recursive

# Set default build mode
build_mode="standard"
is_run=false

# Use getopts to parse command-line options and assign their values to variables
while getopts "f:i" opt; do
  case $opt in
    f)
      build_mode=$OPTARG
      ;;
    i)
      is_run=true
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done

cd "${repo_root}/.${build_mode}-firmware"


# Define the possible file paths
file_path1="firmware/targets/f7/api_symbols.csv"
file_path2="targets/f7/api_symbols.csv"

# Function to extract the API version from a CSV file
extract_api_version() {
    local file_path=$1
    local api_version=$(awk -F',' 'NR == 2 {print $3}' "$file_path")
    echo "$api_version"
}

# Try to extract from the first file path
api_version=$(extract_api_version "$file_path1")

# If the first attempt fails, try the second file path
if [ -z "$api_version" ]; then
    api_version=$(extract_api_version "$file_path2")
fi

# Check if the API version is still not found
if [ -z "$api_version" ]; then
    echo "Error: API version not found in either file path."
else
    echo "API version: $api_version"
fi

app_suffix="${build_mode}_${api_version}"

export FBT_NO_SYNC=1

rm -rf applications_user/$application_name
rm -rf build/f7-firmware-D/.extapps

cp -r ../$application_name/. applications_user/$application_name

if $is_run; then
  ./fbt launch_app APPSRC=$application_name  
else
  ./fbt "fap_${application_name}"
fi

cp "build/f7-firmware-D/.extapps/${application_name}.fap" "../dist/${application_name}_${app_suffix}.fap"
