#include <sys/Application.hpp>
#include <filesystem/DirectoryListing.hpp>
#include <cstring>
#include <ff.h>


int main() {
    sys::Application application;
    filesystem::DirectoryListing listing("0:/");
    return application.exec();
}


