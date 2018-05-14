# poe2d

## Quickstart

```bash
git clone --recursive https://github.com/bernhardfritz/poe2d.git
cd poe2d
mkdir build
cd build
cmake ..
make
./sketch
```

## IntelliSense for vscode

* Press `ctrl/command` + `shift` + `p`
* Select `C/Cpp: Edit Configurations...`
* Edit the `includePath` array:

```JSON
{
    ...
    "includePath": [
        "${workspaceFolder}/include",
        "${workspaceFolder}/lib/libxd/include"
    ]
    ...
}
```
