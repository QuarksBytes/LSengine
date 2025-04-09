import subprocess

subprocess.run(["g++", "test.c", "-o","test","-llua5.4"], check=True)