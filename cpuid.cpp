//
//  main.cpp
//  cpuid
//
//  Created by David Momenso on 10/4/15.
//

#include "CPUID.h"

#include <iostream>
#include <string>


int main(int argc, const char * argv[])
{
    CPUID cpuVendor(0); // Get CPU vendor
    
    std::string vendor;
    vendor += std::string((const char *)&cpuVendor.EBX(), 4);
    vendor += std::string((const char *)&cpuVendor.EDX(), 4);
    vendor += std::string((const char *)&cpuVendor.ECX(), 4);
    
    std::cout << "CPU vendor = " << vendor << std::hex << std::endl;
    
    CPUID processorInfo(1);
    uint32_t info = processorInfo.EAX();
    int stepping = info & 0xf;
    int modelId = (info >> 4) & 0xf;
    int familyId = (info >> 8) & 0xf;
    //int processorType = (info >> 12) & 0x3;
    int extendedModel = (info >> 16) & 0xf;
    int extendedFamily = (info >> 20) & 0xff;
    
    int family = familyId == 0xf ? extendedFamily + familyId : familyId;
    int model = familyId == 0x6 || familyId == 0xf ? (extendedModel << 4) + modelId : modelId;
    
    std::cout << "CPUID           : " << info << std::endl;
    std::cout << "Stepping        : " << stepping << std::endl;
    std::cout << "Model           : " << model << std::endl;
    std::cout << "Family          : " << family << std::endl;
    
    std::string codename = "unknwon";
    switch (info >> 4)
    {
        case 0x506E:
            codename = "Skylake";
            break;
        case 0x406C:
            codename = "CherryTrail";
            break;
        case 0x306D:
            codename = "Broadwell";
            break;
        case 0x306C:
            codename = "Haswell";
            break;
        case 0x306A:
            codename = "IvyBridge";
            break;
        case 0x206A:
        case 0x206D:
            codename = "SandyBridge";
            break;
        case 0x2065:
        case 0x206C:
        case 0x206F:
            codename = "Westmere";
            break;
        case 0x106E:
        case 0x106A:
        case 0x206E:
            codename = "Nehalem";
            break;
        case 0x1067:
        case 0x106D:
            codename = "Penryn";
            break;
        case 0x006F:
        case 0x1066:
            codename = "Merom";
            break;
        case 0x0066:
            codename = "Presler";
            break;
        case 0x0063:
        case 0x0064:
            codename = "Prescott";
            break;
        case 0x006D:
            codename = "Dothan";
            break;
        case 0x0366:
            codename = "Cedarview";
            break;
        case 0x0266:
            codename = "Lincroft";
            break;
        case 0x016C:
            codename = "Pineview";
            break;
    }
    
    std::cout << "Codename        : " << codename << std::endl;
    
    
    return 0;
}
