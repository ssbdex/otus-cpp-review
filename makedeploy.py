import os
project_name = "mypaint"

text = '''{
    "package": {
        "name": project_name,
        "repo": "otus-cpp",
        "subject": "ampermetr123",
        "desc": "Homework 4 of OTUS-CPP course",
        "website_url": "https://ampermetr123.github.io/otus-cpp/",
        "issue_tracker_url": "https://github.com/Ampermetr123/otus-cpp/issues",
        "vcs_url": "https://github.com/Ampermetr123/otus-cpp.git",
        "licenses": ["GPL-2.0"]
    },

    "version": {
        "name": "0.0.$TRAVIS_BUILD_NUMBER",
        "desc": "This is a version"
    },

    "files":
        [{  "includePattern": "{}/build/_CPack_Packages/Linux/DEB/(.*\.deb)".format(project_name), 
            "uploadPattern": "pool/main/{}/{}/$1".format(project_name[0],project_name),
            "matrixParams": {
            "deb_distribution": "trusty",
            "deb_component": "main",
            "deb_architecture": "amd64"}
        }
        ],
    "publish": true

}'''

with open("./deploy.txt","w") as f:
    f.write( text.replace('$TRAVIS_BUILD_NUMBER', os.getenv('TRAVIS_BUILD_NUMBER',0) ))


