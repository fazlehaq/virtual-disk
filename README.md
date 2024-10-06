# Virtual Disk

## Overview

**Virtual Disk** is an advanced, adaptive file system developed in C that provides flexible and efficient file storage solutions. This project allows users to manage their files within a virtual disk, implementing custom encoding/decoding techniques to optimize storage space and handle metadata dynamically.

## Features

- **Custom Variable-Length Encoding/Decoding**: Efficiently manage disk space and metadata without predefined size constraints.
- **File Operations**: Supports essential operations, including:
  - List files (`ls`)
  - Retrieve files (`get`)
  - Remove files (`rm`)
- **Minimal Memory Overhead**: Designed to operate with minimal primary memory usage.
- **Ongoing Development**: Currently implementing features such as:
  - **Defragmentation**: Handling of removed files to optimize storage.
  - **Data Compression**: Techniques to reduce storage space.
  - **Caching**: Improving performance through efficient data retrieval.
  - **Service Prioritization**: Division of services into primary, secondary, and tertiary priorities to enhance user experience.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- Makefile tools

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/fazlehaq/virtual-disk.git
   cd virtual-disk
   ```
2. Build the executable:
   ```bash
   make
   ```
3. Run the executable:
   ```bash
    ./main
   ```
