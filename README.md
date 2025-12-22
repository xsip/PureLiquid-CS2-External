# CS2 External TraceShape Visibility Check

## **External visibility detection for Counter-Strike 2 using remote TraceShape execution.**   

---
[Watch on YouTube](https://www.youtube.com/watch?v=lRgEfxrMk-8)
![CS2 Chams Demo](https://img.youtube.com/vi/lRgEfxrMk-8/maxres2.jpg)
---

## Overview

CS2 External TraceShape Visibility Check is a reverse engineering project that implements accurate player visibility detection for Counter-Strike 2 without DLL injection. The project demonstrates:

- **Remote Function Execution** - Execute CS2's internal TraceShape function from an external process
- **External Process Manipulation** - Comprehensive memory operations without traditional injection techniques

---

## Features

✨ **Authentic Visibility Checking** - Uses CS2's own TraceShape function for accurate line-of-sight detection  
🎯 **External Operation** - No DLL injection required, operates entirely from external process  
🔧 **Real-time Entity Tracking** - Background thread continuously monitors all player entities  
📊 **Dynamic Pattern Scanning** - Automatic function discovery via IDA-style signatures  

---

## How It Works

The system performs visibility checks by:

1. **Pattern Scanning** - Locates CS2's internal TraceShape function using byte signatures
2. **Context Preparation** - Builds reusable TraceFilter and Ray structures in remote memory
3. **Shellcode Injection** - Copies lightweight wrapper code to CS2's address space
4. **Remote Execution** - Creates thread in CS2 that calls the real TraceShape function
5. **Result Retrieval** - Reads trace results to determine if line-of-sight exists

This approach provides the same accuracy as CS2's internal checks while operating entirely externally.

---

## Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    External.exe                         │
│  ┌───────────────────────────────────────────────────┐  │
│  │  Main Thread: Visibility Checking (Left Shift)    │  │
│  └───────────────────────────────────────────────────┘  │
│  ┌───────────────────────────────────────────────────┐  │
│  │  Background Thread: Entity Tracking               │  │
│  └───────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
                          │
                          │ Process Handle
                          ▼
┌─────────────────────────────────────────────────────────┐
│                      cs2.exe                            │
│  ┌───────────────────────────────────────────────────┐  │
│  │  Allocated Memory:                                │  │
│  │  • TraceShapeCtx (parameters)                     │  │
│  │  • TraceFilter_t (entity filtering)               │  │
│  │  • trace_t (results buffer)                       │  │
│  │  • Shellcode (wrapper function)                   │  │
│  └───────────────────────────────────────────────────┘  │
│  ┌───────────────────────────────────────────────────┐  │
│  │  Game Functions (executed remotely):              │  │
│  │  • TraceShape() - Line-of-sight checking          │  │
│  │  • InitTraceFilter() - Filter initialization      │  │
│  └───────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
```

---

## Usage Example

```cpp
int main() {
    
    SetConsoleTitle("xsip's external traceshape visibility check");
    
    // Initialize CS2 interfaces
    I::Initialize();
    
    // Start entity tracking thread
    std::thread([]() { ReadEntititesThread(); }).detach();

    auto pGameEntitySystem = I::pGameResourceService->GetGameEntitySystem();

    // Get local player
    auto lpController = pGameEntitySystem->GetEntityByIndex<CS2::client::CCSPlayerController>(1);
    auto lpPawn = pGameEntitySystem->GetEntityByIndex<CS2::client::C_CSPlayerPawn>(
        lpController->m_hPawn.GetEntryIndex()
    );
    
    // Main loop: Check visibility when left shift is pressed
    while (true) {
        if (!GetAsyncKeyState(VK_LSHIFT)) {
            Sleep(500);
            continue;
        }

        system("cls");
        for (int i = 1; i < 65; i++) {
            auto entity = &CGameEntitySystem::vEntityList[i];

            if (!entity->m_bIsValid || !entity->m_bIsAlive || entity->m_bIsLocalPlayer)
                continue;

            // Perform visibility check using CS2's internal TraceShape
            bool visible = I::pGameTraceManager->IsPlayerVisible(lpPawn, entity->m_pPawn);
            
            printf("Entity %i: %s\n", i, visible ? "Visible" : "Invisible");
        }
    }

    return 0;
}
```

**Example Output:**
```
Entity 2: Visible
Entity 3: Invisible
Entity 5: Visible
Entity 7: Invisible
Entity 9: Visible
```

---

## Hotkeys

| Key | Action                                        |
|-----|-----------------------------------------------|
| **Left Shift (Hold)** | Perform visibility checks and display results |
| **Release** | Pause checking                                |

---

## Technical Highlights

### Remote Code Execution
Shellcode injection enables calling CS2's internal functions with proper context:

```cpp
// Wrapper function (runs in CS2's address space)
DWORD WINAPI TraceShapeThread(LPVOID lpParam) {
    TraceShapeCtx* ctx = (TraceShapeCtx*)lpParam;
    
    // Call CS2's internal function
    ctx->TraceShape(
        ctx->pGameTraceManager,
        ctx->ray,
        ctx->vStartPos,
        ctx->vEndPos,
        ctx->pTraceFilter,
        ctx->pTrace
    );
    
    return 1;
}
```

### Pattern Scanning
IDA-style pattern scanning locates functions dynamically without hardcoded offsets:

```cpp
// Find TraceShape function
TraceShapeFn = pClient->ScanMemory("48 89 5C 24 ?? 48 89 4C 24 ?? 55 57");

// Find TraceFilter initialization
TraceFilterFn = pClient->ScanMemory("48 89 5C 24 ?? 48 89 74 24 ?? 57 48 83 EC ?? 0F B6 41 ?? 33 FF 24");
```

---

## Project Structure

```
CS2-External-TraceShape-Visibility-Check/
├── Memory/              # Low-level memory manipulation
│   ├── Process.h/cpp    # External process memory operations
│   ├── SyscallManager   # Direct NT syscall invocation
│   └── Syscalls_x64.asm # Assembly syscall stubs
├── GlobalData/          # Shared state and utility macros
│   └── Include.h        # PROPERTY macros for external memory access
├── CS2/                 # Counter-Strike 2 SDK
│   ├── Interfaces/      # Game interface abstractions
│   │   ├── Manager.h    # Interface acquisition
│   │   ├── CGameEntitySystem # Entity management
│   │   └── CGameTraceManager # Visibility checking
│   └── SDK/             # Game structures
│       ├── C_CSPlayerPawn
│       ├── CCSPlayerController
│       └── CBaseHandle
└── External/            # Main application
    └── Main.cpp         # Entry point and game loop
```

---

## Building

**Requirements:**
- Visual Studio
- Windows 10/11 SDK
- MASM (Microsoft Macro Assembler)

**Steps:**
1. Open `CS2-External-TraceShape-Visibility-Check.slnx`
2. Set configuration to **Release | x64**
3. Build solution (Ctrl+Shift+B)
4. Output: `Bin/x64/Release/External.exe`

---

## Information

⚠️ **Educational Purpose Only** - This project is for learning about:
- Windows process internals and memory manipulation
- Game engine reverse engineering
- Direct syscall invocation

Compile in **Release mode** for optimal performance and correct shellcode generation.

---

## Credits

- **Unknowncheats** for CS2 structure research and entity system documentation

---

## License

This project is provided for **educational and research purposes only**. Using this software in online games violates Terms of Service and may be illegal. The author assumes no responsibility for misuse.

---

## Other Projects
[CS2-External-Chams](https://github.com/xsip/CS2-External-Chams)
