#include<bits\stdc++.h>
#include<fstream>
#include<windows.h>

using namespace std;

class todo
{
    char task[100];
    public:
    todo()
    {
    }
    void disp()
    {
        cout << task;
    }
    void add(char* a2)
    {
      strcpy(task, a2);
    }
};
void readdata();
void writedata();
class taskdata
{
    public:
    int notask, nocompleted;
     
    taskdata()
    {
          readdata();
    }
      ~taskdata()
    {
        writedata();
    }
}taskdat;
void readdata()
{
    ifstream fin("taskdata.txt", ios::in|ios::out);
    if(!fin)
    {
        taskdat.notask=0;
        taskdat.nocompleted=0;   
    }
    else
    {
        fin.read((char*)&taskdat, sizeof(taskdat));
    }
    fin.close();
}
void writedata()
{
    ofstream fout("taskdata.txt", ios::out);
    fout.write((char*)&taskdat, sizeof(taskdat));
}
void reporthelp()
{
    cout << "Usage :-\n$ ./todo add \"todo item\"  # Add a new todo\n$ ./todo ls               # Show remaining todos\n$ ./todo del NUMBER       # Delete a todo\n$ ./todo done NUMBER      # Complete a todo\n$ ./todo help             # Show usage\n$ ./todo report           # Statistics\n";}
void crack(int argn, char* args[])
{
    if(argn==1)
    {
        reporthelp();
    }
    else 
    {
        todo ob;   
        string a1=args[1];
        if(a1=="add")
        {
            if(argn==2)
            {
               cout << "Error: Missing todo string. Nothing added!\n";
               return;
            }
               cout << "Added todo: \"" << args[2] << "\"\n";
            ifstream ff("tasks.txt", ios::in);
            ofstream ff2("tasks2.txt", ios::out);
            ob.add(args[2]);            
            ff2.write((char*) &ob, sizeof(ob));
            int temp=taskdat.notask;
            if(ff)
            while(temp--)
            {
                ff.read((char*) &ob, sizeof(ob));
                ff2.write((char*) &ob, sizeof(ob));
            }
            ff2.close();
            ff.close();
            remove("tasks.txt");
            rename("tasks2.txt", "tasks.txt");
            taskdat.notask++;
         
          }
        else if(a1=="ls")
        {
  if(taskdat.notask==0)
  {
      cout << "There are no pending todos!\n";
      return;
  }
            ifstream ff("tasks.txt", ios::in);
            if(ff)
            {
                int temp=taskdat.notask;
                while(temp--)
                {
                    ff.read((char*) &ob, sizeof(ob));
                    cout << "[" << temp+1 << "] \"";
                    ob.disp();
                    cout << "\"\n";
                }
            }
            ff.close();
        }
        else if(a1=="report")
        {
            std::time_t t = std::time(0);   
    std::tm* now = std::localtime(&t);
    cout << now->tm_mday << '/'  << (now->tm_mon + 1) << '/' <<  (now->tm_year + 1900);
           cout << " Pending : " << taskdat.notask << " Completed : " << taskdat.nocompleted << "\n";
        }
        else if(a1=="help")
        {
            reporthelp();
        }
        else if(a1=="done")
        {
            if(argn==2)
            {
                cout << "Error: Missing NUMBER for marking todo as done.\n";
                return;
            }
            int num=0;
            for(int i=0;i<strlen(args[2]);i++)
            {
                num=num*10+args[2][i]-48;
            }
            if(num<=taskdat.notask&&num>0)
            {
                cout << "Marked todo #" << num << " as done.\n";
            } 
            else
            {
            
                cout << "Error: todo #" << num << " does not exist.\n";
                return;
            
            }
            
            ifstream ff("tasks.txt", ios::in);
            ofstream ff2("tasks2.txt", ios::out);
            int temp=taskdat.notask;
            if(ff)
            while(temp--)
            {
                ff.read((char*) &ob, sizeof(ob));
                if((temp+1)==num)
                continue;
                ff2.write((char*) &ob, sizeof(ob));
            }
                       
            ff2.close();
            ff.close();
            remove("tasks.txt");
            rename("tasks2.txt", "tasks.txt");
            taskdat.notask--;
            taskdat.nocompleted++;
        }
        else if(a1=="del")
        {
            if(argn==2)
            {
                cout << "Error: Missing NUMBER for deleting todo.\n";return;
            }
            int num=0;
            for(int i=0;i<strlen(args[2]);i++)
            {
                num=num*10+args[2][i]-48;
            }
            if(num<=taskdat.notask&&num>0)
            {
                cout << "Deleted todo #" << num << "\n";    
            }
            else
            {
                cout << "Error: todo #" << num << " does not exist. Nothing deleted.\n";return;
            }
            ifstream ff("tasks.txt", ios::in);
            ofstream ff2("tasks2.txt", ios::out);
            int temp=taskdat.notask;
            if(ff)
            while(temp--)
            {
                ff.read((char*) &ob, sizeof(ob));
                if((temp+1)==num)
                continue;
                ff2.write((char*) &ob, sizeof(ob));
            }
            else
            {
                cout << "No Such Task!\n";
            }
            
            ff2.close();
            ff.close();
            remove("tasks.txt");
            rename("tasks2.txt", "tasks.txt");
            taskdat.notask--;
        }
        else
        {
            /* code */
        }
        
          
        
        
    }
    
}

int main(int argn, char* args[])
{
    
    crack(argn, args);
    

}