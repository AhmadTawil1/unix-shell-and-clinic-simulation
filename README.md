# Project Overview

This repository contains two main directories, each containing different system implementations:

## Sem_ Directory
The `Sem_` directory contains a multithreaded dental clinic simulation implemented in C using POSIX threads and semaphores.

### Project Description
A simulation of a dental clinic with:
- 3 hygienist threads
- N patient threads (N > 3)
- 4 standing spaces
- 1 sofa
- 3 treatment chairs

### System Components
- `ex3.c`: The main implementation file containing:
  - Patient and hygienist thread implementations
  - Semaphore management for synchronization
  - Resource management (sofa, chairs, standing spaces)
  - Payment processing system
- `ex3.out`: Compiled output of the simulation
- `מערכות הפעלה.docx`: Documentation including:
  - Team member information
  - Program output screenshots
  - Implementation details

### Key Features
- Thread synchronization using POSIX threads and semaphores
- Resource management for clinic capacity
- Queue management for patient waiting
- Payment processing system
- Real-time status updates

## UNIX Directory
The `UNIX` directory contains a Linux-based shell system implementing a loan request platform using low-level system calls.

### Project Description
A shell-based loan management system with two modes:
- MainShell: For normal users
- ManagerShell: For administrative functions

### System Components

#### MainShell Features
- `Main_shell.c`: Primary user interface
- `GetLoan.c`: Create new loan requests
- `CheckStatus.c`: View request status
- `ApproveLoan.c`: Final approval processing
- `LoginM.c`: Manager authentication
- `exit.c`: Session termination

#### ManagerShell Features
- `Manager_shell.c`: Administrative interface
- `ShowReqNum.c`: Total request statistics
- `ShowAReqNum.c`: Approved request count
- `ShowUnReqNum.c`: Rejected request count
- `CheckRequestList.c`: Pending request management
- `ShowReqDetails.c`: Detailed request information
- `ShowCriteria.c`: Credit rating criteria display
- `UpdateCriteria.c`: Criteria management
- `ApproveReqLoan.c`: Request approval processing
- `UnApprovedReqLoan.c`: Request rejection
- `LogOut.c`: Manager session termination

### System Structure
- Directories:
  - `Loan/Request/`
  - `Loan/Result/Approved/`
  - `Loan/Result/UnApproved/`
- Files:
  - `User.txt`
  - `Criteria.txt`
  - `Manager_pass.txt`
  - Individual request files (`<ID>.txt`)

### Technical Requirements
- Uses only low-level system calls (open, read, write)
- No system, fork, or exec calls
- Shell script (`Sys_shell.sh`) for compilation and execution

## Getting Started

### For Sem_ Project:
1. Compile the program using a C compiler with POSIX thread support
2. Run the executable to start the simulation
3. Use Ctrl+C to terminate the simulation

### For UNIX Project:
1. Run `Sys_shell.sh` to compile and start the system
2. Use MainShell for regular user operations
3. Use ManagerShell for administrative functions

## Requirements
- C compiler with POSIX thread support (for Sem_)
- Linux/Unix environment
- Word document viewer (for documentation)
- Shell environment (for UNIX project) 