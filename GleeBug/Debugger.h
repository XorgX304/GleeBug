#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "Debugger.Global.h"
#include "Debugger.Process.h"
#include "Debugger.Breakpoint.h"

namespace GleeBug
{
    /**
    \brief A debugger class.
    */
    class Debugger
    {
    public: //public functionality
        /**
        \brief Constructs the Debugger instance.
        */
        Debugger();

        /**
        \brief Destructs the Debugger instance.
        */
        virtual ~Debugger();

        /**
        \brief Start the debuggee.
        \param szFilePath Full pathname of the file to debug.
        \param szCommandLine The command line to pass to the debuggee.
        \param szCurrentDirectory Pathname of the current directory.
        \return true if the debuggee was started correctly, false otherwise.
        */
        bool Init(const wchar_t* szFilePath,
            const wchar_t* szCommandLine,
            const wchar_t* szCurrentDirectory);

        /**
        \brief Stops the debuggee (terminate the process)
        \return true if the debuggee was stopped correctly, false otherwise.
        */
        bool Stop() const;

        /**
        \brief Detaches the debuggee.
        \return true if the debuggee was detached correctly, false otherwise.
        */
        bool Detach() const;

        /**
        \brief Run the debug loop (does not return until the debuggee is detached or terminated).
        */
        void Start();

    protected: //debug event callbacks
        /**
        \brief Generic pre debug event callback. Called before the event is internally processed. Provide an implementation to use this callback.
        \param debugEvent The debug event.
        */
        virtual void cbPreDebugEvent(const DEBUG_EVENT & debugEvent) {};

        /**
        \brief Generic post debug event callback. Called after the event is internally processed. Provide an implementation to use this callback.
        \param debugEvent The debug event.
        */
        virtual void cbPostDebugEvent(const DEBUG_EVENT & debugEvent) {};

        /**
        \brief Process creation debug event callback. Called after the event is internally processed. Provide an implementation to use this callback.
        \param createProcess Information about the process created.
        \param process ProcessInfo of the created process.
        */
        virtual void cbCreateProcessEvent(const CREATE_PROCESS_DEBUG_INFO & createProcess, const ProcessInfo & process) {};

        /**
        \brief Process termination debug event callback. Called before the event is internally processed. Provide an implementation to use this callback.
        \param exitProcess Information about the process terminated.
        \param process ProcessInfo of the terminated process.
        */
        virtual void cbExitProcessEvent(const EXIT_PROCESS_DEBUG_INFO & exitProcess, const ProcessInfo & process) {};

        /**
        \brief Thread creation debug event callback. Called after the event is internally processed. Provide an implementation to use this callback.
        \param createThread Information about the thread created.
        \param thread ThreadInfo of the created thread.
        */
        virtual void cbCreateThreadEvent(const CREATE_THREAD_DEBUG_INFO & createThread, const ThreadInfo & thread) {};

        /**
        \brief Thread termination debug event callback. Called before the event is internally processed. Provide an implementation to use this callback.
        \param exitThread Information about the thread terminated.
        \param thread ThreadInfo of the terminated thread.
        */
        virtual void cbExitThreadEvent(const EXIT_THREAD_DEBUG_INFO & exitThread, const ThreadInfo & thread) {};

        /**
        \brief DLL load debug event callback. Called after event is internally processed. Provide an implementation to use this callback.
        \param loadDll Information about the DLL loaded.
        \param dll DllInfo of the loaded DLL.
        */
        virtual void cbLoadDllEvent(const LOAD_DLL_DEBUG_INFO & loadDll, const DllInfo & dll) {};

        /**
        \brief DLL unload debug event callback. Called before event is internally processed. Provide an implementation to use this callback.
        \param unloadDll Information about the DLL unloaded.
        \param dll DllInfo of the unloaded DLL.
        */
        virtual void cbUnloadDllEvent(const UNLOAD_DLL_DEBUG_INFO & unloadDll, const DllInfo & dll) {};

        /**
        \brief Exception debug event callback. Called before the event is internally processed. Provide an implementation to use this callback.
        \param exceptionInfo Information about the exception.
        */
        virtual void cbExceptionEvent(const EXCEPTION_DEBUG_INFO & exceptionInfo) {};

        /**
        \brief Debug string debug event callback. Called before the event is internally processed. Provide an implementation to use this callback.
        \param debugString Information about the debug string.
        */
        virtual void cbDebugStringEvent(const OUTPUT_DEBUG_STRING_INFO & debugString) {};

        /**
        \brief RIP debug event callback. Called before the event is internally processed. Provide an implementation to use this callback.
        \param rip Information about the RIP event.
        */
        virtual void cbRipEvent(const RIP_INFO & rip) {};

        /**
        \brief Unknown event callback. Called before the event is internally processed. Provide an implementation to use this callback.
        \param debugEventCode The debug event code.
        */
        virtual void cbUnknownEvent(DWORD debugEventCode) {};

    protected: //other callbacks
        /**
        \brief Internal error callback. Provide an implementation to use this callback.
        \param error The error message.
        */
        virtual void cbInternalError(const std::string & error) {};

        /**
        \brief Unhandled exception callback. Called after the exception event is processed. Provide an implementation to use this callback.
        \param exceptionRecord The exception record.
        \param firstChance True if the exception is a first chance exception, false otherwise.
        */
        virtual void cbUnhandledException(const EXCEPTION_RECORD & exceptionRecord, bool firstChance) {};

        /**
        \brief System breakpoint callback. Called after the event is internally processed. Provide an implementation to use this callback.
        */
        virtual void cbSystemBreakpoint() {};

        /**
        \brief Step callback. Called before any user callbacks. Provide an implementation to use this callback.
        */
        virtual void cbStep() {};

        /**
        \brief Breakpoint callback. Called before any user callbacks. Provide an implementation to use this callback.
        \param info The breakpoint information.
        */
        virtual void cbBreakpoint(const BreakpointInfo & info) {}

    protected: //core debug event handlers
        /**
        \brief Process creation debug event. Do not override this unless you know what you are doing!
        \param createProcess Information about the process created.
        */
        virtual void createProcessEvent(const CREATE_PROCESS_DEBUG_INFO & createProcess);

        /**
        \brief Process termination debug event. Do not override this unless you know what you are doing!
        \param exitProcess Information about the process terminated.
        */
        virtual void exitProcessEvent(const EXIT_PROCESS_DEBUG_INFO & exitProcess);

        /**
        \brief Thread creation debug event. Do not override this unless you know what you are doing!
        \param createThread Information about the thread created.
        */
        virtual void createThreadEvent(const CREATE_THREAD_DEBUG_INFO & createThread);

        /**
        \brief Thread termination debug event. Do not override this unless you know what you are doing!
        \param exitThread Information about the thread terminated.
        */
        virtual void exitThreadEvent(const EXIT_THREAD_DEBUG_INFO & exitThread);

        /**
        \brief DLL load debug event. Do not override this unless you know what you are doing!
        \param loadDll Information about the DLL loaded.
        */
        virtual void loadDllEvent(const LOAD_DLL_DEBUG_INFO & loadDll);

        /**
        \brief DLL unload debug event. Do not override this unless you know what you are doing!
        \param unloadDll Information about the DLL unloaded.
        */
        virtual void unloadDllEvent(const UNLOAD_DLL_DEBUG_INFO & unloadDll);

        /**
        \brief Exception debug event. Do not override this unless you know what you are doing!
        \param exceptionInfo Information about the exception.
        */
        virtual void exceptionEvent(const EXCEPTION_DEBUG_INFO & exceptionInfo);

        /**
        \brief Debug string debug event. Do not override this unless you know what you are doing!
        \param debugString Information about the debug string.
        */
        virtual void debugStringEvent(const OUTPUT_DEBUG_STRING_INFO & debugString);

        /**
        \brief RIP debug event. Do not override this unless you know what you are doing!
        \param rip Information about the RIP event.
        */
        virtual void ripEvent(const RIP_INFO & rip);

        /**
        \brief Unknown event. Do not override this unless you know what you are doing!
        \param debugEventCode The debug event code.
        */
        virtual void unknownEvent(DWORD debugEventCode);

    protected: //core exception handlers
        /**
        \brief Breakpoint exception handler. Do not override this unless you know what you are doing!
        \param exceptionRecord The exception record.
        \param firstChance True if the exception is a first chance exception, false otherwise.
        */
        virtual void exceptionBreakpoint(const EXCEPTION_RECORD & exceptionRecord, bool firstChance);

        /**
        \brief Single step exception handler. Do not override this unless you know what you are doing!
        \param exceptionRecord The exception record.
        \param firstChance True if the exception is a first chance exception, false otherwise.
        */
        virtual void exceptionSingleStep(const EXCEPTION_RECORD & exceptionRecord, bool firstChance);

        /**
        \brief Hardware breakpoint (single step) exception handler. Do not override this unless you know what you are doing!
        \param exceptionAddress The exception address.
        */
        virtual void exceptionHardwareBreakpoint(ptr exceptionAddress);

    protected: //variables
        PROCESS_INFORMATION _mainProcess;
        uint32 _continueStatus = DBG_EXCEPTION_NOT_HANDLED;
        bool _breakDebugger = false;
        DEBUG_EVENT _debugEvent;
        ProcessMap _processes;
        bool _isRunning = false;
        bool _isDebugging = false;

        /**
        \brief The current process (can be null in some cases).
        */
        ProcessInfo* _process = nullptr;

        /**
        \brief The current thread (can be null in some cases). Should be a copy of _process->thread.
        */
        ThreadInfo* _thread = nullptr;

        /**
        \brief The current thread registers (can be null in some cases). Should be a copy of _thread->registers.
        */
        Registers* _registers = nullptr;
    };
};

#endif //DEBUGGER_H