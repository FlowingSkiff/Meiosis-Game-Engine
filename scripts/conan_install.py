import os
import sys

def printHelp():
    print("Help message")

def runConanInstall(conan_profile):
    conan_command = "conan install .. -pr {} -pr:b {} --build missing -if {}"
    conan_folder = os.path.join(os.path.dirname(os.path.dirname(__file__)), "conan")
    profile_dict = {
        "r-msvc": "msvc",
        "r-gcc": "gcc-win",
        "d-msvc": "msvc",
        "d-gcc": "d-gcc-win"
    }
    conan_install_folder = os.path.join(conan_folder, profile_dict[conan_profile])
    os.system(conan_command.format(conan_profile, conan_profile, conan_install_folder))
    


if __name__ == '__main__':
    if (len(sys.argv) < 2):
        printHelp()
    else:
        runConanInstall(sys.argv[1])