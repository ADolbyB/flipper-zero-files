# Stand up to hate against minorities, silence is violence!

# Flipper zero community badusb payload library
The idea is to put all the fz friendly scripts in one place like the IRDB in one master library so we can all just git pull the updates.

If you are looking for the resources these duckies use or for resources to build your own duckies head over to my [BadUSB-Playground](https://github.com/FalsePhilosopher/BadUSB-Playground) repo.<br>

# Contributing
## Please adhere to the following best practices and style guides when submitting a payload.

## Naming Conventions
Please give your payload a unique, descriptive and appropriate name. Do not use spaces in payload, directory or file names. Each payload should be submit into its own directory, with `-` or `_` used in place of spaces, to one of the categories such as exfiltration, phishing, remote_access or recon. Do not create your own category.

## Staged Payloads
"Staged payloads" are payloads that **download** code from some resource external to the payload.txt. 

While staging code used in payloads is often useful and appropriate, using this (or another) github repository as the means of deploying those stages is not. This repository is **not a CDN for deployment on target systems**. 

Staged code should be copied to and hosted on an appropriate server for doing so **by the end user** - Github and this repository are simply resources for sharing code among developers and users.
See: [GitHub acceptable use policies](https://docs.github.com/en/site-policy/acceptable-use-policies/github-acceptable-use-policies#5-site-access-and-safety)

Additionally, any source code that is intended to be staged **(by the end user on the appropriate infrastructure)** should be included in any payload submissions either in the comments of the payload itself or as a seperate file. **Links to staged code are unacceptable**; not only for the reasons listed above but also for version control and user safety reasons. Arbitrary code hidden behind some pre-defined external resource via URL in a payload could be replaced at any point in the future unbeknownst to the user -- potentially turning a harmless payload into something dangerous.

## Payload Documentation
Payloads should begin with `REM` comments specifying the title of the payload, the author, the target, and a brief description.

    REM Title: Canary Duck
	REM Author: Jessie Crimson Hart
	REM Description: Opens hidden powershell and connects to canary webserver using Invoke-WebRequest alerting you to spies and snoops.
	REM Target: Windows 10 (Powershell)
	REM Props: Hak5, Thinkst
	REM Version: 1.0
	REM Category: General

Payloads from this repository are provided for educational purposes only.  Hak5/FZ gear is intended for authorized auditing and security analysis purposes only where permitted subject to local and international laws where applicable. Users are solely responsible for compliance with all laws of their locality. FalsePhilosopher and affiliates claim no responsibility for unauthorized or unlawful use.

# Disclaimer
<h3><b>As with any script, you are advised to proceed with caution.</h3></b>
<h3><b>Generally, payloads may execute commands on your device. As such, it is possible for a payload to damage your device. Payloads from this repository are provided AS-IS without support. While I make a best effort to review payloads, there are no guarantees as to their effectiveness.</h3></b>
