Cutting
=======


Download
--------
Make sure to clone all submodules as well:

```bash
git clone --recursive https://gitlab.com/LoganBarnes/cnc.git
```

If the project was already cloned without submodules use this command from the root folder:

```bash
git submodule update --init --recursive
```


Build and Run
-------------

### Unix

```bash
cd run
./unixConfigureAndBuild.sh
./bin/runCutting
```


### Windows

```batch
cd run
winConfigureAndBuild.cmd
bin\runCutting.exe
```


