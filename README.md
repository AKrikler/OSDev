# OSDEV

A custom 32-bit operating system built from scratch for the x86 architecture.

## Project Architecture

* **`common/`**: Platform-independent type definitions and shared headers.
* **`src/arch/i386/`**: Hardware Abstraction Layer (HAL) including boot logic and GDT/IDT setups.
* **`src/kernel/`**: High-level kernel logic (Memory management, scheduling, etc.).
* **`build/`**: Destination for compiled object files and the final bootable ISO.

## Prerequisites

- **Docker**: For compiling the source.
- **QEMU**: For emulating the hardware and running the ISO.

## Getting Started

### 1. Build the Toolchain
First, create the Docker image containing the necessary compilers (`gcc`, `nasm`) and ISO tools (`grub`, `xorriso`):
```bash
docker build -t osdev-env .
```
### 2. Compile the Project
Use the container to run the Makefile. This will generate the kernel binary and the bootable ISO:
```bash
docker run --rm -v "$(pwd):/root/env" osdev-env make
```
### 3. Run the OS
```bash
qemu-system-i386 -cdrom build/osdev.iso
```
## Roadmap
- [ ] Hardware Setup
    - [ ] Project & Docker Setup
    - [ ] Bootloader & Linker
    - [ ] VGA Text Mode Driver
    - [ ] GDT Setup
    - [ ] Setup IDT & ISRs
    - [ ] Remap PIC & IRQs
- [ ] Memory Management
    - [ ] TBD
- [ ] Multitasking & Scheduling
    - [ ] TBD
- [ ] Virtual File System (VFS) & Storage
    - [ ] TBD
- [ ] User Mode & System Calls
    - [ ] TBD
- [ ] Userspace & Applications
    - [ ] TBD
## License
This project is licensed under the MIT License - see the LICENSE file for details.