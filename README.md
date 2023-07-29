# LoadLibrary-DLL-Injector
A simple open-source console LoadLibrary DLL Injector.

## Usage
### Cloning
Git is required in order to clone a github repository. You can find a download to git on their official website <a href="https://git-scm.com/">here</a>.
After installing git, open CMD and enter this command:
<pre><code>git clone https://github.com/morganwall/LoadLibrary-DLL-Injector.git</code></pre>
You should have now successfully cloned the repository.
### Requirements
This project was writen in Microsoft Visual Studio 2019 and will require platform toolset v142 or higher.
This project was wrote and will only run on Windows.
### Compiling
First, please make sure that you have Microsoft Visual Studio 2019 or higher intalled, along with platform toolset v142 or above.
Open the .sln file included in the folder using with Microsoft Visual Studio.
After that, select the build options that correlate to the architecture of your desired target program <code>Release | x64/x86</code> and press Build.
Upon completion, you should find a binary called "LoadLibrary DLL Injector.exe".
### Operation
After launching the exe, you will be greeted by a console window.
You will first be asked to enter the name of your DLL file <code>e.g. Internal</code>, followed by the name of the target process <code>e.g. notepad</code>.
NOTE: Do not include file extentions in the file name. Also please make sure that your DLL file is placed in the same path as the built binary.
### License
<blockquote>Copyright (c) 2023 Morgan Wall</blockquote>
This project is licensed under the <a href="https://choosealicense.com/licenses/gpl-3.0/">GNU General Public License v3.0 License</a> - refer to the <a href="https://github.com/morganwall/LoadLibrary-DLL-Injector/blob/main/LICENSE">LICENSE</a> for more detail.
