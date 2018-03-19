import java.io.*;
import java.lang.*;
import java.util.*;

public class Scheduler
{
    static Process currentProcess = null;
    
    public static void main(String[] args)
    {
        File inputFile;
        int numProcesses = 0;
        Process[] processes = new Process[4];
        Scanner keyboard = new Scanner(System.in);

        // open input file
        String inputFileName = "";
        if(args.length > 0)
        {
            inputFileName = args[0];
        }
        else
        {
            System.out.print("Enter a file name: ");
            inputFileName = keyboard.next();
        }
        inputFile = new File(inputFileName);
        

        try {
            Scanner file = new Scanner(inputFile);

            // read first line to get number of processes
            String line1 = file.nextLine();
            Scanner scanLine = new Scanner(line1);
            numProcesses = scanLine.nextInt();
            scanLine.close();

            // save num processes in variable
            processes = new Process[numProcesses];

            // read i amount of lines from file where i is number of processes
            for (int i = 0; i < numProcesses; i++)
            {
                // split the current line into tokens
                // expects [arrival] [priority] [burst time]
                String[] str = file.nextLine().split(" ");
                // initialize int array to convert input tokens to ints
                int[] in = new int[str.length];

                // convert input tokens to integers
                for(int s = 0; s < str.length; s++)
                {
                    try {
                        in[s] = Integer.parseInt(str[s]);
                    } catch (NumberFormatException e) {
                        break;
                    }
                }

                // create a new process with the specified parameters
                processes[i] = new Process(Character.toString(IntToLetter(i)), in[0], in[1], in[2]);
            }
            file.close();

        } catch (FileNotFoundException e) {
            System.err.println("File not found.");
        }

        // list all processes taken from the file
        for(int i = 0; i < numProcesses; i++)
        {
            System.out.println(processes[i].toString());
        }

        // create variables for the simulation
        List<Process> queue = new ArrayList<Process>();
        List<Process> start = new ArrayList<Process>();
        List<Process> complete = new ArrayList<Process>();
        int time = processes[0].arrival;
        int nextProccessUp = 0;
        int completedProcesses = 0;
        GanttChart chart = new GanttChart();
        int timeQuantum = 2;
        int q = 0;
        double cpuSpeed = 1.0;

        // if a command line arg is passed for quantum, apply it
        // else prompt user
        if(args.length > 1)
        {
            timeQuantum = Integer.parseInt(args[1]);
        }
        else
        {
            System.out.print("Enter the time quantum (deafult 2): ");
            if(keyboard.hasNextInt())
            timeQuantum = keyboard.nextInt();
        }
        // if a command line arg is passed for simulation speed, apply it
        // else prompt user
        if(args.length > 2)
        {
            cpuSpeed = Float.parseFloat(args[2]);
        }
        else
        {
            System.out.print("Enter the CPU simulation speed (deafult 1s): ");
            if(keyboard.hasNextDouble())
            cpuSpeed = keyboard.nextDouble();
        }

        // no reason to wait at the start of the simulation
        // if the first arrival is not 0
        // notify the user it was changed
        if(time > 0)
            System.out.println("First process arrives at time " + time + ". Advancing cpu start time for convenience");

        System.out.println("Time Quantum: " + timeQuantum);
        System.out.println("Press the 'Enter' key to begin execution...");
        // wait for user input to continue
        try {
            System.in.read();
        } catch (Exception e) {}

        // run while there are still processes to run
        while(completedProcesses < numProcesses)
        {
            // as long as there are processes not in queue yet
            // enter them into queue
            if(nextProccessUp < numProcesses)
            {
                // when the next input process arrival time is equal to the current cpu time
                if(time == processes[nextProccessUp].arrival)
                {
                    // add that process to the run queue
                    queue = EnterProcessIntoQueue(processes[nextProccessUp], queue);
                    // move on to the next from input
                    nextProccessUp++;
                }
            }

            // if there is no current process
            // try to get one from the queue
            if(currentProcess == null)
            {
                SetCurrentProcess(PopFromQueue(queue), "There is no current process, get one from queue");
                q = 0;
            }
            
            // as long as there is a process to run
            if(currentProcess != null)
            {
                // if there is something in the queue
                if(queue.size() > 0)
                {
                    // if the current process and the first item in queue have the same priority
                    if(queue.get(0).priority == currentProcess.priority)
                    {
                        // start using quantum
                        // if the quantum is equal to the max quantum
                        // then enter current process into queue
                        // and get the first process in the queue
                        if(q >= timeQuantum)
                        {
                            EnterProcessIntoQueue(currentProcess, queue);
                            SetCurrentProcess(PopFromQueue(queue), "Quantum = Max Quantum | q=" + q);
                            q = 0;
                        }
                    }
                    // if current process has less priority than first item in queue
                    // then swap them
                    else if (queue.get(0).priority < currentProcess.priority)
                    {
                        EnterProcessIntoQueue(currentProcess, queue);
                        SetCurrentProcess(PopFromQueue(queue), "Lower priority");
                        q = 0;
                    }
                }
                q++;
                
                // if the current process is not displayed in the chart
                // then it is the first time it is running
                // set the start time of the process
                if(!chart.contains(currentProcess.name))
                {
                    currentProcess.start = time;
                    start.add(currentProcess);
                }

                // add the current process to the chart
                chart.Add(time, currentProcess.name);
                currentProcess.cpu--;
                
                // if the current process has completed running
                // then set the exit time of the process
                if(currentProcess.cpu == 0)
                {
                    currentProcess.exit = time+1;
                    complete.add(currentProcess); 
                    completedProcesses++;

                    // try to get next process
                    SetCurrentProcess(PopFromQueue(queue), "CPU is at 0");
                    q = 0;
                }
                
                // print out info to screen
                WriteOut(chart, queue, currentProcess, start, complete);
            }

            // increment time and go to ne cycle
            time++;

            try {
                Thread.sleep( (long)(cpuSpeed * 1000.0));
            } catch (InterruptedException e) {}
        }

        System.out.println("Simulation Complete.");
        
        // display turnaround times
        System.out.println("Turnaround Times...");
        ProcessTurnaroundTimes(processes);

        keyboard.close();
    }

    
    public static void SetCurrentProcess(Process p, String why)
    {
        System.out.print("Current process: " + currentProcess);
        currentProcess = p;
        System.out.println(" | Switching to " + currentProcess + " because: " + why);
    }

    // clear console and print out state information
    public static void WriteOut(GanttChart chart, List<Process> queue, Process dispatch, List<Process> started, List<Process> completed)
    {
        // clearConsole();
        PrintQueue(queue);
        System.out.print("Started: ");
        for (int c = 0; c < started.size(); c++) {
            System.out.print(String.format("%s(time %d) ", started.get(c).name, started.get(c).start));
        }
        System.out.println();
        System.out.println("Dispatching: " + (dispatch != null ? dispatch.name : ""));
        System.out.print("Completed: ");
        for (int c = 0; c < completed.size(); c++) {
            System.out.print(String.format("%s(time %d) ", completed.get(c).name, completed.get(c).exit));
        }
        System.out.println();
        System.out.println(chart.GetTimes());
        System.out.println(chart.GetHistory());
    }

    private static void clearConsole() {
        try {
          final String os = System.getProperty("os.name");
          if (os.contains("Windows")) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
          } else {
                System.out.print("\033[H\033[2J");
          }
        } catch (final Exception e) {}
      }
    

    // Process gets inserted into queue based on priority.
    // "Lowest" number priority first.
    static List<Process> EnterProcessIntoQueue(Process process, List<Process> queue)
    {
        int index = 0;
        for(int i = 0; i < queue.size(); i++)
        {
            // current < q0 = current has higher priority
            if(process.priority >= queue.get(i).priority)
            {
                index++;
                continue;
            }
        }
        queue.add(index, process);
        return queue;
    }

    // get lowest priotity process from queue
    static Process PopFromQueue(List<Process> queue)
    {
        if (queue.size() > 0)
            return queue.remove(0);
        else
            return null;
    }

    static void PrintQueue(List<Process> queue)
    {
        System.out.print("Queue: ");
        for(int i = 0; i < queue.size(); i++)
        {
            System.out.print(queue.get(i).name + " ");
        }
        System.out.println();
    }

    static char IntToLetter(int i)
    {
        return (char)(i+65);
    }

    // subtract the arrival time from the exit time to get the turnaround time for each process
    // then add it all up and divide by number of proceses to get the average turnaround time
    static void ProcessTurnaroundTimes(Process[] processes)
    {
        int total = 0;
        for (int i = 0; i < processes.length; i++) {
            int turnaround = processes[i].exit - processes[i].arrival;
            total += turnaround;
            System.out.println(String.format("%-5s: %3d - %-3d = %-4d", processes[i].name, processes[i].exit, processes[i].arrival, turnaround));
        }

        System.out.println(String.format("%-17s= %d", "Total", total));
        System.out.println(String.format("%-17s= %f", "Avg. Turnaround", (float)total/(float)processes.length));
    }
}

class Process
{
    public String name;
    public int priority;
    public int arrival;
    public int cpu;
    public int start;
    public int exit;

    public Process(String _name, int _arrival, int _priority, int _cpu)
    {
        name = _name;
        arrival = _arrival;
        priority = _priority;
        cpu = _cpu;
        start = 0;
        exit = 0;
    }

    public String toString()
    {
        return name + " -- a:" + arrival + " p:" + priority + " c:" + cpu;
    }
}

class GanttChart
{
    List<Integer> times = new ArrayList<Integer>();
    List<String> names = new ArrayList<String>();

    public void Add(int time, String name)
    {
        times.add(time);
        names.add(name);
    }

    public String GetTimes()
    {
        String str = "";

        for(int i = 0; i < times.size(); i++)
            str += String.format("%-3d", times.get(i));
            
        return str;
    }
    // returns a list of the names of processes in the chart
    public String GetHistory()
    {
        String str = "";

        for(int i = 0; i < names.size(); i++)
            str += String.format("%-3s", names.get(i));
            
        return str;
    }

    public boolean contains(String name)
    {
        return names.contains(name);
    }
}