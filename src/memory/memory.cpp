#include <boot/boot.hpp>
#include <interrupt/interrupt.hpp>
#include <memory/memory.hpp>

#define SET_GDT_DESCRIPTOR(base, limit, access, flags) \
    {                                                  \
        (uint16_t)(limit),                             \
            (uint16_t)(base),                          \
            (uint8_t)((base) >> 16),                   \
            (access),                                  \
            (uint8_t)((limit) >> 16),                  \
            (uint8_t)(flags),                          \
            (uint8_t)((base) >> 24),                   \
    }

namespace
{
    const size_t MAX_DESCRIPTOR_NUMBER = 10;
    const system::memory::entity::GdtDescriptor gdtTable[MAX_DESCRIPTOR_NUMBER] = {
        // base, limit, access, flags
        SET_GDT_DESCRIPTOR(0, 0, 0, 0),                     // 0 NULL descriptor 0x00
        SET_GDT_DESCRIPTOR(0, 0, 0b10011000, 0b0010),       // 1 Kernel Code 64-bit Segment 0x08
        SET_GDT_DESCRIPTOR(0, 0, 0b10010010, 0b0000),       // 2 Kernel Data 64-bit Segment 0x10
        SET_GDT_DESCRIPTOR(0, 0, 0b11111000, 0b0010),       // 3 User Code 64-bit Segment 0x18
        SET_GDT_DESCRIPTOR(0, 0, 0b11110010, 0b0000),       // 4 User Data 64-bit Segment 0x20
        SET_GDT_DESCRIPTOR(0, 0xfffff, 0b10011010, 0b1100), // 5 Kernel Code 32-bit Segment 0x28
        SET_GDT_DESCRIPTOR(0, 0xfffff, 0b10010010, 0b1100), // 6 Kernel Data 32-bit Segment 0x30
    };

    extern "C" const system::memory::entity::GdtTableDescriptor gdtTableDescriptor = {
        sizeof(gdtTable) * 8 - 1, // size of GDT
        (uint64_t)gdtTable        // addr of GDT
    };
} // namespace

namespace system::init
{
    void initMemory()
    {
        int count = system::boot::getBootInfo()->memoryInfo.count;

        unsigned long usableMemory = 0;
        const system::boot::entity::MemoryDescriptor *descriptors = system::boot::getBootInfo()->memoryInfo.descriptors;
        int i = 0;
        for (; i < count && i < system::memory::entity::GlobalMemoryDescriptor::MEMORY_DESCRIPTORS_COUNT_MAX; i++)
        {
            if (descriptors[i].type == system::memory::entity::MemoryDescriptorType::RAM)
            {
                usableMemory += descriptors[i].length;
                system::memory::getGlobalMemoryDescriptor()->memoryDescriptors[i].free = true;
            }

            system::memory::getGlobalMemoryDescriptor()->memoryDescriptors[i].address = descriptors[i].address;
            system::memory::getGlobalMemoryDescriptor()->memoryDescriptors[i].length = descriptors[i].length;
            system::memory::getGlobalMemoryDescriptor()->memoryDescriptors[i].type = (system::memory::entity::MemoryDescriptorType)descriptors[i].type;

            // must be dirty data
            if (descriptors[i].length == 0 || descriptors[i].type < system::memory::entity::MemoryDescriptorType::RAM || descriptors[i].type > system::memory::entity::MemoryDescriptorType::UNUSABLE)
            {
                break;
            }
        }

        system::memory::getGlobalMemoryDescriptor()->memoryDescriptorsCount = i;
        system::memory::getGlobalMemoryDescriptor()->usableMemory = usableMemory;

        unsigned long usablePages = 0;
        for (int i = 0; i < system::memory::getGlobalMemoryDescriptor()->memoryDescriptorsCount; i++)
        {
            if (system::memory::getGlobalMemoryDescriptor()->memoryDescriptors[i].type != system::memory::entity::MemoryDescriptorType::RAM)
            {
                continue;
            }

            usablePages += system::memory::getGlobalMemoryDescriptor()->memoryDescriptors[i].pages();
        }
        system::memory::getGlobalMemoryDescriptor()->usablePages = usablePages;
    }

} // namespace system::init
