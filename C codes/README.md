# Municipal Financial Management System (MFMS)

## Group Information
- **Group Name:** MFMS
- **Group Number:** Group 5
- **Names & Student Numbers:**
  - Alfeus Rosalia — 224009893 
  - Nangolo Drothea — 223039985  
  - Siyanda Ndhlovu - 223127981   
  - Andreas Niipare  -223118958  
  - Allan Lunga     - 225061333   
  -
- **Course:** PAP521S – Programming in Practice
- **Institution:** Namibia University of Science and Technology

## Project Description
A menu-driven system to manage municipal employees, budgets, suppliers, assets, and generate reports — developed as Project A foundation system.

## System Features
- Employee Management — Add, display, search, calculate salaries
- Budget Management — Set department budgets, record expenditure, check status
- Supplier Management — Register, list, search suppliers
- Asset Management — Register assets, search by ID
- Reports — Individual & combined reports
- Full input validation

Compilation Instructions
```bash
gcc main.c employees.c budget.c suppliers.c assets.c reports.c -o mfms 
.\mfms.exe

Responsibilities 
  -Alfeus Rosalia -Employee Management
  - Nangolo Drothea  -Supplier Management
  - Siyanda Ndhlovu  -Asset Management
  - Andreas Niipare  -Budget Management
  - Allan Lunga     - Report Management

 6. Function, Integration, and Validation

Function
The system has **five core management modules**:

- Employee Management
  - Adds, displays, searches employees; calculates salaries
  - Stores: names, IDs, department, salary, contact details

- Budget Management
  - Sets department budgets; records expenditure; checks budget status
  - Tracks: allocated budget, amount spent, remaining balance

- Supplier Management 
  - Registers new suppliers; displays all; searches by name
  - Stores: supplier name, contact person, phone, email, address
  - Key functions: `addSupplier()`, `displayAllSuppliers()`, `searchSupplier()`, `handleSupplierMenu()`

- Asset Management
  - Registers assets; searches by ID; lists all assets
  - Stores: asset ID, name, type, value, department, condition

- Report Generation
  - Generates individual and combined reports for all modules
  - Summarizes totals and status across the system

Integration
- All modules connect through **`main.c`** — one central main menu
- Each module has its own `.h` header file that declares public functions
- `main.c` includes all headers → calls each module’s menu function → returns to main menu when finished
- Common data types and limits defined in shared headers ensure consistency

 Validation Applied Across All Modules
- Empty input rejection — cannot save blank/required fields
- Length limits — names, IDs, emails cannot exceed defined maximums
- Numeric range checks — menu choices only accept valid option numbers
- Full list prevention — shows message when storage limit reached
- Data format checks — ensures correct types entered for numbers and IDs

  7. Testing, Documentation, and Git Coordination

Testing
- Unit Testing
  - **Supplier Management 
    - Created `test_suppliers.c` to run independently without other modules
    - Verified: add supplier, display list, search, empty list, full list, invalid input
  - Employee Management
    - Tested: add employee, search, calculate salary, display all
  - Budget Management
    - Tested: set budget, record spending, check remaining balance
  - Asset Management
    - Tested: register asset, search by ID, list all assets

- Integration Testing
  - Compiled full system:
    ```bash
    gcc main.c employees.c budget.c suppliers.c assets.c reports.c -o mfms
    ```
  - Ran end-to-end: main menu → enter each module → return to main → exit
  - Verified all modules work together without conflicts

- **Test Cases Run — All Modules:**
  - Supplier Management — Add new supplier → saves & displays correctly
  - Supplier — Empty list → shows "No suppliers registered"
  - Supplier — Search existing → finds & shows details
  - Supplier — Search non-existent → shows "Not found"
  - Supplier — List full → rejects new entries with message
  - Employee Management — Add employee → displays; search by name → finds match
  - Budget Management — Set budget → record expense → updates remaining
  - Asset Management — Add asset → search by ID → returns correct record
  - System-wide— Invalid menu choice → shows error & prompts again
  - All modules → return to main menu correctly

Documentation
- Every `.c` and `.h` file includes:
  - Module description at the top
  - Author name & student number
  - Function purpose comments
- **README.md** contains: project overview, group members, responsibilities, compile/run instructions, and this full report
- Consistent naming, indentation, and formatting applied across all files

Git Coordination
- All code stored in shared GitHub repository
- Workflow followed for every update:
  ```bash
  git add .
  git commit -m "Description of changes"
  git push

