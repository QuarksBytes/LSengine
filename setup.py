import subprocess
import shutil

installForApt="sudo apt-get install "
installForPacman="sudo pacman -S "
installForDnf="sudo dnf install "
installForYum="sudo yum install "
installForApk="sudo apk add "


def install_packages():
    packages = [
        "gcc",
        "g++",
        "gdb",             # debugger
        "lua",
        "python3",  # Python development files
        "python-pip",  # Python package manager
    ]
    
   
    if shutil.which("apt"):
        subprocess.run(installForApt.split(" ")+packages)
    elif shutil.which("dnf"):
        subprocess.run(installForDnf.split(" ")+packages)
    elif shutil.which("yum"):
        subprocess.run(installForYum.split(" ")+packages)
    elif shutil.which("pacman"):
        subprocess.run(installForPacman.split(" ")+packages)
    elif shutil.which("apk"):
        subprocess.run(installForApk.split(" ")+packages)
    else:
        printf("[ Error ] : Package manager not found")
        

if __name__ == "__main__":
    install_packages()


    

