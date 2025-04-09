import subprocess

def install_packages():
    packages = [
        "build-essential",  # gcc, g++, make, etc.
        "gdb",              # debugger
        "lua5.4",
        "liblua5.4-dev",  # Lua development files
    ]
    
    print("Updating package list...")
    subprocess.run(["sudo", "apt", "update"], check=True)

    print("Installing C/C++ development packages...")
    subprocess.run(["sudo", "apt", "install", "-y"] + packages, check=True)

    print("✅ Installation complete!")

if __name__ == "__main__":
    try:
        install_packages()
    except subprocess.CalledProcessError as e:
        print(f"❌ Command failed: {e}")
