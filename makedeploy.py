import os

text = '''{
    "package": {
        "name": "print_ip",
        "repo": "otus-cpp",
        "subject": "ampermetr123",
        "desc": "Homework 3 of OTUS-CPP course",
        "website_url": "www.jfrog.com",
        "issue_tracker_url": "https://github.com/Ampermetr123/otus-cpp/issues",
        "vcs_url": "https://github.com/Ampermetr123/otus-cpp.git",
        "licenses": ["GPL-2.0"]
    },

    "version": {
        "name": "0.0.$TRAVIS_BUILD_NUMBER",
        "desc": "This is a version"
    },

    "files":
        [{"includePattern": "allocator/build/_CPack_Packages/Linux/DEB/(.*\.deb)", "uploadPattern": "pool/main/a/allocator/$1",
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


