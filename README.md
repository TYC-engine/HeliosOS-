# ☀️ HeliosOS

<div align="center">

# HeliosOS

**Experimental Operating System Written From Scratch**

![Version](https://img.shields.io/badge/version-0.1.0-blue)
![Status](https://img.shields.io/badge/status-development-orange)
![Architecture](https://img.shields.io/badge/architecture-x86-lightgrey)
![Language](https://img.shields.io/badge/language-C%20%7C%20Assembly-green)
![License](https://img.shields.io/badge/license-Apache-purple)

*Building an operating system from the boot sector to the kernel.*

</div>

---

## 📖 About

HeliosOS is an educational operating system project focused on understanding:

* Operating System Development
* Computer Architecture
* Bootloaders
* x86 Assembly
* Kernel Design
* Memory Management
* Graphics Programming

The project aims to create a complete operating system using custom technologies and components.

---

## ✨ Features

### Current

* [x] Custom Bootloader
* [x] Kernel Entry Point
* [x] VGA Text Output
* [x] Basic Console
* [x] Keyboard Input
* [x] Framebuffer
* [x] Protected mode
* [x] GUI
### Planned


* [ ] Memory Manager
* [ ] User Applications
* [ ] Networking
* [ ] Helios Package Manager

---

## 📸 Screenshots

### Boot Process

```text
          [Helios boot...]
```

### Terminal

```text
HeliosOS v1

helios>_
```

---

## 🏗 Architecture

```text
+-----------------------+
|      Applications     |
+-----------------------+
|      Helios Shell     |
+-----------------------+
|        Kernel         |
+-----------------------+
|      Bootloader       |
+-----------------------+
|       BIOS/UEFI       |
+-----------------------+
|       Hardware        |
+-----------------------+
```

---

## 📂 Project Structure

```text
HeliosOS
│
├── boot/
│   ├── boot.asm
│   ├── gdt.asm
│   ├── protected.asm
│   ├── a20.asm
│   ├── kernel_entry.asm
|   └── stage2.asm
│
│
├── kernel/
│   ├── gui
│       ├── gui.h
|       ├── gui.c
│       ├── window.c
|       └── window.h
│   ├── gfx
│       ├── compositor.h
│       ├── compositor.c
│       ├── gdi.h
│       ├── gdi.c
│       ├── surface.h
│       └── sufrace.c
│   ├── input
│       ├── mouse.h
│       ├── mouse.c
│       ├── ps2.h
│       └── ps2.c
│   ├── framebuffer.h
│   ├── framebuffer.c
│   ├── kernel.c
│   ├── kernel.h
│   ├── pit.c
│   ├── irq.asm
│   ├── irq12.asm
│   ├── isr.asm
│   ├── interrupts.c
│   ├── interrupts.h
│   ├── keyboard.c
│   ├── keyboard.h
│   ├── idt.c
│   ├── idt.h
│   ├── ha.h
│   ├── ports.h
│   ├── ports.c
│   ├── pit.h
│   ├── shell.c
│   ├── screen.h
│   ├── screen.c
├── fs
│   ├── fat32.h
│   ├── fat32.c
│   ├── disk.h
│   ├── disk.c
│   ├── ata.h
│   └── ata.c
│
├── LICENCE
│
└── README.md
```

---

## ⚙️ Requirements

| Tool               | Purpose            |
| ------------------ | ------------------ |
| NASM               | Assembler          |
| GCC Cross Compiler | Kernel Compilation |
| Make               | Build System       |
| QEMU               | Emulation          |
| Git                | Version Control    |
│ This tools         | for me and for you |
│ there will be a    │ ready-made assembly│

---

## 🚀 Build

### Compile

```bash
make
```

### Run

```bash
qemu-system-i386 -drive format=raw,file=helios.img
```

### Debug

```bash
qemu-system-i386 -s -S -drive format=raw,file=helios.img
```

---

## 🧠 Boot Flow

```text
Power On
    │
    ▼
BIOS
    │
    ▼
Bootloader
    │
    ▼
Kernel Loader
    │
    ▼
Kernel Initialization
    │
    ▼
Drivers
    │
    ▼
Helios Shell
```

---

## 🛣 Roadmap

| Feature         | Status         |
| --------------- | -------------- |
| Bootloader      | ✅ Complete     |
| Kernel Entry    | ✅ Complete     |
| VGA Driver      | ✅ Complete     |
| Keyboard Driver | ✅ Complete     |
| Protected Mode  | ✅ Complete     |
| Memory Manager  | ✅ Complete     |
| Interrupts      | ✅ Complete     |
| File System     | ✅ Complete     |
| Multitasking    | ✅ Complete     |
| Networking      | ✅ Complete     |
| GUI             | ✅ Complete     |
| HASM Compiler   | 🟡 In work      |
| Package Manager | 🟡 In work      |

---

## 🔧 Helios Technologies

### HASM

Helios Assembly Language.

Example:

```asm
section .text

start:
    print "Hello HeliosOS"
    halt
```

### HA Executable Format

```text
program.ha
```

Future executable format designed for HeliosOS.

---

## 🎯 Long-Term Goals

* Custom Bootloader
* Custom Kernel
* Custom Executable Format
* Custom Programming Language
* Custom GUI
* Custom Package Manager
* Educational Documentation

---

## 📊 Development Status

```text
Bootloader        ██████████ 100%
Kernel            ██████████ 100%
Drivers           ██████████ 100%
Memory Manager    ███████░░░  70%
File System       █████████░  90%
GUI               ██████████ 100%
```

---

## 🤝 Contributing

Contributions, bug reports, ideas, and documentation improvements are welcome.

1. Fork repository
2. Create branch
3. Commit changes
4. Open pull request

---

## 📜 License

Apache 2.0 License

Copyright (c) HeliosOS Project

---

<div align="center">

### ☀️ HeliosOS

*"From Boot Sector to Operating System."*

</div>
