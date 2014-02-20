# CoD4 RCON status patch
#### What does it solve?
It solves bad status parses on server side (Usually a `0.0.0.0` bug in parser type addons). All CoD4 addons (Except for Alice) are parsers (Much like B3). The addon will request a "status" package from the server. The packets are sent back to the addon to parse out the IP of each player. The CoD4 server will sometimes drop a single byte off the end of the packet, sometimes resulting in a bad parse of the status.

#### What causes this?
It's caused by a short buffer within CoD4 Server. The buffer is `1044` bytes long when it should actually be `1045` bytes long to deal with the ending character (Usually 0x00).

#### How do I use this patch?
##### Compile or Binary
You can use this patch by either:
  * Compile by running `make` in the root of the repo  
    -OR-
  * [Download](https://github.com/Zinglish/cod4-patch-rstatus/blob/master/cod4-patch-rstatus-deb-x64?raw=true) the ELF that's already precompiled for x64 Debian flavours of Linux.  

##### Usage
Binary takes 1 parameter. The last parameter of the command should be the path to the CoD4 Server binary you wish to patch. EG: `cod4-patch-rstatus-deb-x64 cod4-server-linded`.

### Patching details
This patcher hard patches the short byte inside the ELF.
```text
 --------------------------
| OFFSET     | FROM | TO   |
|------------|------|------|
| 0x001305E2 | 0x14 | 0x15 |
 --------------------------
```

### Bugs
No existing issues are created when this patch has been applied. No bugs exist within the patcher either.
