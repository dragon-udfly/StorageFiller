# StorageFiller 

A lightweight C utility designed to fill up disk storage programmatically by creating and writing data blocks to the file system.

---

## 📂 Repository Structure

```text
StorageFiller/
│
├── fill_drive.c    # Core C program that handles drive space exhaustion logic
├── LICENSE         # Open-source license governing the repository
└── .gitignore      # Specifies intentionally untracked files to ignore
```

## 🧠 Logic & Implementation Explanation
1. The core program (fill_drive.c) operates using low-level file stream and block-writing techniques in C:
2. Target Allocation: The program targets a specified path or directory on the file system to begin writing filler data.
3. Buffered Data Blocks: It allocates a memory buffer filled with predefined bytes or repeating characters to optimize throughput.
- Continuous Write Loop (fwrite / write):
  - A continuous loop opens a destination file and writes chunks of data block-by-block.
  - This loop continues execution until the underlying storage disk returns a full status (i.e., ENOSPC - No space left on device) or hits user-defined size bounds.
  - Safety & Cleanup: Ensures file descriptors and streams are safely handled to prevent memory leaks during disk exhaustion.
