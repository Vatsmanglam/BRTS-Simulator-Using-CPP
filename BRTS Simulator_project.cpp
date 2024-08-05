#include<iostream>
#include <cstdlib>
#include<string>
#include<queue>

using namespace std;

#define MAX_STATIONS 20
#define MAX_BUSES 100
#define MAX_EMPLOYEES 100
#define BUS_CAPACITY 100
#define MAX_PASSENGERS 100
#define CASHIER_SALARY 15000
#define DRIVER_SALARY 10000

class BRTSExceptions {

};

class Person {
protected:
    string Name;
    int age;
    string AdharCard;
public:
    Person() {}
    Person(string name,int age,string AdharCard) {
        this->Name=name;
        this->age=age;
        this->AdharCard=AdharCard;
    }
    Person(string name,int age) {
        this->Name=name;
        this->age=age;
        this->AdharCard=AdharCard;
    }
    void DisplayDetails() {
        if(Name!="") cout << "Name: " << Name << endl;
        cout << "Age: " << age << endl;
        if(AdharCard!="") cout << "AdharCard: " << Name << endl;
    }
};

class Employee:public Person {
    int Employeeid;
    int Salary;
    string Work;
public:
    Employee() {
    }
    Employee(int Employeeid,string name,int age,string AdharCard,string work,int Salary):Person(name,age,AdharCard) {
        this->Employeeid=Employeeid;
        this->Salary=Salary;
        Work=work;
    }
    void UpdateSalary(int newsalary) {
        Salary=newsalary;
    }
    void PrintEmployee() {
        cout << "Employee Type: " << Work << endl;
        cout << "Employee id: " << Employeeid << endl;
        cout << "Name: " << Name << endl;
        cout << "Age: " << age << endl;
        cout << "Salary: " << Salary << endl;
    }
};

class Driver: public Employee {
    public:
    Driver() {}
    Driver(int Employeeid,string name,int age,string AdharCard):Employee(Employeeid,name,age,AdharCard,"Driver",DRIVER_SALARY) {
    }
};

class Cashier: public Employee {
    public:
        Cashier() {}
        Cashier(int Employeeid,string name,int age,string AdharCard):Employee(Employeeid,name,age,AdharCard,"Cashier",CASHIER_SALARY) {
        }
};

class BusStation {
    string StationName;
    float DistanceFromStart;
public:
    Cashier cashier;
    BusStation() {}
    BusStation(string StationName,float Distance) {
        this->StationName=StationName;
        DistanceFromStart=Distance;
    }
    void AddCashier(Cashier e) {
        cashier=e;
    }
    int CalcuateFare(float DestinationKM) {
        int BasePrice=6;
        int Calc=DestinationKM/1.5;
        int Price=BasePrice + (Calc-1)*BasePrice;
        return Price;
    }
    float Distance() {
        return DistanceFromStart;
    }
    string getName() {
        return StationName;
    }
};

class Bus {
    string VehicleNo;
    int capacity;
public:
    string bustype;
    BusStation current_station;
    Driver driver;
    Bus() {}
    Bus(string VehicleNo,int capacity,string bustype,BusStation CurLocation) {
        this->VehicleNo=VehicleNo;
        this->capacity=capacity;
        this->bustype=bustype;
        current_station=CurLocation;
    }
    void AddDriver(Driver d) {
        driver=d;
    }
    void DisplayBus() {
        cout << "BUS: "<< bustype << endl;
        cout << "Vehicle Number: " << VehicleNo << endl;
        cout << "Current Station: " << current_station.getName() << endl;
    }
    void updateLocation(BusStation newlocation) {
        current_station=newlocation;
    }
    string getVhno() {
        return VehicleNo;
    }
};

class Passenger;

class Payments {
protected:
    int fare;
    bool ispaid;
public:
    string PaymentMethod;
    Payments(int fare) {
        this->fare=fare;
        ispaid=false;
        PaymentMethod="NULL";
    }
    bool isPaid() {
        return ispaid;
    }
    void Pay(Passenger *p);
};

class UPI: public Payments {
    string upiid;
public:
    UPI(string id,int fare):Payments(fare) {
        upiid=id;
        PaymentMethod="UPI";
    }
};

class Cash: public Payments {
public:
    Cash(int fare):Payments(fare) {
        PaymentMethod="Cash";
    }
};

class TravelBy {
protected:
    BusStation *SourceLocation;
    BusStation *Destination;
    int fare;
public:
    TravelBy() {}
    TravelBy(BusStation *SourceLocation,BusStation *Destination,int fare) {
        this->SourceLocation=SourceLocation;
        this->Destination=Destination;
        this->fare=fare;
    }
    int getFare() {
        return fare;
    }
};

/*
class Date {
    bool Verify(int DD, int MM, int YYYY) {
        if(DD>31||DD<0) return false;
        if(MM>12||DD<0) return false;
        if(YYYY<0) return false;
        return true;
    }
protected:
    int DD;
    int MM;
    int YYYY;
public:
    Date(int DD,int MM,int YYYY) {
        if(!Verify(DD,MM,YYYY)) {
            //Throw
        } else {
            this->DD=DD;
            this->MM=MM;
            this->YYYY=YYYY;
        }
    }

};
*/

class BusPass:public TravelBy {
    int PassId;
public:
    BusPass() {}
    BusPass(int id,BusStation *SourceLocation,BusStation *Destination) {
        PassId=id;
        this->SourceLocation=SourceLocation;
        this->Destination=Destination;
    }
    bool VerifyTravel(BusStation *s,BusStation *d) {
        if(s->getName()==SourceLocation->getName()&&d->getName()==Destination->getName()) return true;
        if(d->getName()==SourceLocation->getName()&&s->getName()==Destination->getName()) return true;
        return true;
    }
    void printBusPass() {
        cout << "Bus Pass ID: " << PassId << endl;
        cout << "Valid For" << endl;
        cout << "- " << SourceLocation->getName() << endl;
        cout << "- " << Destination->getName() << endl;
    }
};

class Ticket:public TravelBy {
    UPI *pay1;
    Cash *pay2;
public:
    Ticket() {}
    Ticket(BusStation *SourceLocation,BusStation *Destination,int fare):TravelBy(SourceLocation,Destination,fare) {
        cout << "Select Mode of Payment" << endl;
        cout << "1. UPI" << endl;
        cout << "2. Cash" << endl;
        int ch;
        cin >> ch;
        if(ch==1) {
            string upiid;
            cout << "Enter UPI id:" << endl;
            cin >> upiid;
            //pay1=new UPI(upiid,fare);
            //pay1->Pay();
        } else {
            //pay2=new Cash(fare);
            //pay2->Pay();
        }
    }
};

class Passenger: public Person {
bool HasBusPass;
int pid;
int money;
public:
    BusStation CurrentLocation;
    BusPass pass;
    Ticket ticket;
    Passenger() {}
    Passenger(int pid,int money,string name,int age,BusStation cloc):Person(name,age) {
        HasBusPass=false;
        this->money=money;
        this->pid=pid;
        CurrentLocation=cloc;
    }
    void BuyBussPass(BusPass bp) {
        if(HasBusPass==false) {
            if(money>=200) {
                HasBusPass=true;
                money=money-200;
                pass=bp;
            }
        }
    }
    bool DeductMoney(int f) {
        if(money>f) {
            money=money-f;
            return true;
        }
        return false;
    }
    bool hasPass() {
        return HasBusPass;
    }
    void BuyTicket(Ticket tk) {
        int fare=tk.getFare();
    }
    void printp() {
        cout << "Person ID: " << pid << endl;
        Person::DisplayDetails();
        cout << "Money: " << money << endl;
        cout << "Location: " << CurrentLocation.getName() << endl;
    }
    string printname() {
        return Name;
    }
    int getId() {
        return pid;
    }
};

void Payments::Pay(Passenger *p) {
    cout << "Payment Complete via " << PaymentMethod << endl;
    if(p->DeductMoney(fare)) {
        ispaid=true;
    }
}

class BRTS {
protected:
    Bus *Chigris;
    Driver *emps1;
    Cashier *emps2;
    BusStation *stations;
    Passenger *passengers;
    int TotalVehicles;
    int TotalStations;
    int TotalPassengers;
    string Location;
public:
    BRTS(string location) {
        TotalVehicles=0;
        TotalStations=0;
        TotalPassengers=0;
        Chigris=new Bus[MAX_BUSES];
        emps1=new Driver[MAX_EMPLOYEES];
        emps2=new Cashier[MAX_EMPLOYEES];
        passengers=new Passenger[MAX_PASSENGERS];
        stations=new BusStation[MAX_STATIONS];
        Location=location;
    }
    void addBus() {
        Bus b=createBus();
        Driver e=HireDriver();
        b.AddDriver(e);
        Chigris[TotalVehicles]=b;
        TotalVehicles++;
    }
    void addStation() {
        BusStation bs=createstation();
        Cashier e=HireCashier();
        bs.AddCashier(e);
        stations[TotalStations]=bs;
        TotalStations++;
    }
    void addStation(BusStation bs, Cashier e) {
        emps2[TotalStations]=e;
        bs.AddCashier(e);
        stations[TotalStations]=bs;
        TotalStations++;
    }
    void addBus(Bus b,Driver e) {
        b.AddDriver(e);
        emps1[TotalVehicles]=e;
        Chigris[TotalVehicles]=b;
        TotalVehicles++;
    }
    Driver HireDriver() {
        string name,card;
        int age;
        cout << "Enter Employee Name:";
        cin >> name;
        cout << "Enter Employee Age:";
        cin >> age;
        cout << "Enter Adhar Card:";
        cin >> card;
        Driver e(TotalStations+TotalVehicles+1,name,age,card);
        emps1[TotalStations]=e;
        TotalStations++;
        return e;
    }
    Cashier HireCashier() {
        string name,card;
        int age;
        cout << "Enter Employee Name:";
        cin >> name;
        cout << "Enter Employee Age:";
        cin >> age;
        cout << "Enter Adhar Card:";
        cin >> card;
        Cashier e(TotalStations+TotalVehicles+1,name,age,card);
        emps2[TotalVehicles]=e;
        TotalVehicles++;
        return e;
    }
    void reset() {
        TotalStations=0;
        TotalVehicles=0;
    }
    void printBuses() {
        cout << "============" << endl;
        cout << "BRTS BUSES" << endl;
        cout << "============" << endl;
        for(int i=0;i<TotalVehicles;i++) {
            Chigris[i].DisplayBus();
        }
    }
    void printStations() {
        cout << "BRTS STATION" << endl;
        for(int i=0;i<TotalStations;i++) {
            cout << stations[i].getName() << endl;
        }
    }
    void printEmplyee() {
        cout << "BRTS EMPLOYEES" << endl;
        for(int i=0;i<TotalStations;i++) {
            stations[i].cashier.PrintEmployee();
            cout << "Currently Working in Station: " << stations[i].getName() << endl << endl;
        }
        for(int i=0;i<TotalVehicles;i++) {
            Chigris[i].driver.PrintEmployee();
            cout << "Currently Working Driving: " << Chigris[i].getVhno() << endl << endl;
        }
    }
    Bus createBus() {
        string vh,bt;
        cout << "Enter Vehicle NO" << endl;
        cin >> vh;
        cout << "Enter BUS Type(200A/200B)" << endl;
        cin >> bt;
        int loc=rand()%TotalStations;
        Bus b1(vh,BUS_CAPACITY,bt,stations[loc]);
        return b1;
    }
    BusStation createstation() {
        string name;
        float dist;
        cout << "Enter Station name" << endl;
        cin >> name;
        if(TotalStations==0) {
            dist=0;
        } else {
            cout << "Enter Distance from " << stations[0].getName() << " :";
            cin >> dist;
        }
        BusStation b1(name,dist);
        return b1;
    }
    void FindFareBetweenStation() {
        cout << "BRTS STATION" << endl;
        for(int i=0;i<TotalStations;i++) {
            cout << i+1<< ") "<< stations[i].getName() << endl;
        }
        int c1,c2;
        cout << "Enter Source:";
        cin >> c1;
        cout << "Enter Destination:";
        cin >> c2;
        int fare=stations[c1-1].CalcuateFare(stations[c2-1].Distance());
        cout << "Total Fare:" << fare << endl;
    }
    void Addpass() {
        string name,adh;
        int age,money;
        cout << "Enter Name:" << endl;
        cin >> name;
        cout << "Enter Age:" << endl;
        cin >> age;
        cout << "Enter Money:" << endl;
        cin >> money;
        for(int i=0;i<TotalStations;i++) {
            cout << i+1<< ") "<< stations[i].getName() << endl;
        }
        int c1;
        cout << "Enter Source:";
        cin >> c1;
        Passenger p(TotalPassengers+1,money,name,age,stations[c1-1]);
        passengers[TotalPassengers]=p;
        TotalPassengers++;
    }
    void Addpass(Passenger p) {
        passengers[TotalPassengers]=p;
        TotalPassengers++;
    }
    void printPass() {
        for(int i=0;i<TotalPassengers;i++) {
            passengers[i].printp();
            if(passengers[i].hasPass()) {
                cout << "Has Bus Pass: True" << endl;
                passengers[i].pass.printBusPass();
            } else {
                cout << "Has Bus Pass: False" << endl;
            }
            cout << endl;
        }
    }
    void buyBuspass() {
        int id,c;
        cout << "Enter ID:" << endl;
        cin >> id;
        for(int i=0;i<TotalPassengers;i++) {
            if(passengers[i].getId()==id) {
                c=i;
                break;
            }
        }
        for(int i=0;i<TotalStations;i++) {
            cout << i+1<< ") "<< stations[i].getName() << endl;
        }
        int c1,c2;
        cout << "Enter Source:";
        cin >> c1;
        cout << "Enter Destination:";
        cin >> c2;
        char ch;
        cout << "Do You Want to Buy Bus Pass for Rs 200? [Y/N]" << endl;
        cin >> ch;
        if(ch=='N'||ch=='n') return;
        cout << "Payment Options" << endl;
        cout << "1. UPI" << endl;
        cout << "2. Cash" << endl;
        int ch1;
        cin >> ch1;
        if(ch1==1) {
            string upi;
            cout << "Enter UPI ID" << endl;
            cin >> upi;
            UPI pay(upi,200);
            pay.Pay(&passengers[c]);
            if(!pay.isPaid()) {
                cout << "Payment Failed !!" << endl;
                return;
            }
        } else if(ch1 ==2) {
            Cash pay(200);
            pay.Pay(&passengers[c]);
            if(!pay.isPaid()) {
                cout << "Payment Failed !!" << endl;
                return;
            }
        }
        BusPass B(id,&stations[c1-1],&stations[c2-1]);
        passengers[c].BuyBussPass(B);
    }
    void movebus() {
        for(int i=0;i<TotalVehicles;i++) {
            int index=getStationIndex(Chigris[i].current_station);
            if(index==0&&Chigris[i].bustype=="200B") {
                Chigris[i].bustype="200A";
            } else if(index==TotalStations-1&&Chigris[i].bustype=="200A") {
                Chigris[i].bustype="200B";
            } else if(Chigris[i].bustype=="200B") {
                Chigris[i].updateLocation(stations[index-1]);
            } else if(Chigris[i].bustype=="200A") {
                Chigris[i].updateLocation(stations[index+1]);
            }
        }
    }
    int getStationIndex(BusStation bs) {
        for(int i=0;i<TotalStations;i++) {
            if(bs.getName()==stations[i].getName()) {
                return i;
            }
        }
        return -1;
    }
    void simulatePerson() {
        int id,c;
        cout << "Enter ID:" << endl;
        cin >> id;
        for(int i=0;i<TotalPassengers;i++) {
            if(passengers[i].getId()==id) {
                c=i;
                break;
            }
        }
        simulate(&passengers[c]);
    }
    void simulate(Passenger *p) {
        string name=p->printname();
        cout << "Passenger: " << name << endl;
        cout << "Location: " << p->CurrentLocation.getName() << endl;
        cout << "=============" << endl;
        cout << "1. Travel" << endl;
        cout << "2. Exit" << endl;
        cout << "=============" << endl;
        int ch;
        cin >> ch;
        if(ch==1) {
            cout << "BRTS STATION" << endl;
            for(int i=0;i<TotalStations;i++) {
                cout << i+1<< ") "<< stations[i].getName() << endl;
            }
            int c1;
            cout << "Enter Destination:";
            cin >> c1;
            cout << "Fare is " << p->CurrentLocation.CalcuateFare(abs(stations[c1].Distance()-p->CurrentLocation.Distance()));

        }
    }
};

/*
class TravelSimulation: public BRTS {
    BusStation *SourceLocation;
    BusStation *Destination;
    int fare;
public:
    TravelSimulation(BusStation *Source,BusStation *Dest,bool HasBusPass) {
        SourceLocation=Source;
        Destination=Destination;
        //this->HasBusPass=HasBusPass;
        //if(HasBusPass) {
            //pass=new BusPass;
        //} else {
            //ticket=new Ticket(SourceLocation,Destination,SourceLocation->CalcuateFare(Destination->Distance()));
        //}
    }
    int AddPass(string name,int age,BusPass pass) {
        this->Name=name;
        this->age=age;
        if(!pass.Verify(name,age)) {
            return 0;
        }
        if(!pass.VerifyTravel(SourceLocation,Destination)) {
            return 0;
        }
        this->pass=&pass;
        return 1;
    }
};
*/

void defualtValues(BRTS *b) {
    BusStation B1("KLE TEch",0);
    BusStation B2("Vidya Nagar",1.2);
    BusStation B3("KIIMS",2.4);
    BusStation B4("Hossur Bus Stand",3.5);
    BusStation B5("Hossur Cross",4);
    BusStation B6("HDMC",4.5);
    BusStation B7("Dr Ambedkar Circle",5.2);
    BusStation B8("Railway Station",6);
    BusStation B9("CBT",6.7);
    Cashier C1(1,"Raj",35,"QWERTY1234");
    Cashier C2(2,"Rajiv",42,"QWERTY1235");
    Cashier C3(3,"Mohan",38,"QWERTY1236");
    Cashier C4(4,"Sohan",54,"QWERTY1237");
    Cashier C5(5,"Rohan",36,"QWERTY1238");
    Cashier C6(6,"Rohit",39,"QWERTY1239");
    Cashier C7(7,"Sohit",61,"QWERTY1210");
    Cashier C8(8,"Manan",49,"QWERTY1211");
    Cashier C9(9,"Harshit",47,"QWERTY1212");
    Bus A1("KA1234AB",BUS_CAPACITY,"200A",B1);
    Bus A2("KA1235AB",BUS_CAPACITY,"200B",B2);
    Bus A3("KA1236AB",BUS_CAPACITY,"200A",B3);
    Bus A4("KA1237AB",BUS_CAPACITY,"200B",B4);
    Bus A5("KA1238AB",BUS_CAPACITY,"200A",B5);
    Bus A6("KA1239AB",BUS_CAPACITY,"200B",B6);
    Bus A7("KA1230AB",BUS_CAPACITY,"200A",B7);
    Bus A8("KA1244AB",BUS_CAPACITY,"200B",B8);
    Bus A9("KA1254AB",BUS_CAPACITY,"200A",B9);
    Bus A10("KA1264AB",BUS_CAPACITY,"200B",B1);
    Driver D1(11,"Raj",35,"ABRDEF1234");
    Driver D2(12,"Rajiv",42,"ABRDEF1235");
    Driver D3(13,"Mohan",38,"ABRDEF1236");
    Driver D4(14,"Sohan",54,"ABRDEF1237");
    Driver D5(15,"Rohan",36,"ABRDEF1238");
    Driver D6(16,"Rohit",39,"ABRDEF1239");
    Driver D7(17,"Sohit",61,"ABRDEF1210");
    Driver D8(18,"Manan",49,"ABRDEF1211");
    Driver D9(19,"Harshit",47,"ABRDEF1212");
	Driver D10(10,"Kumar",42,"ABRDEF1298");

	Passenger P1(1,500,"Shivan",20,B1);
	Passenger P2(2,1000,"Somil",20,B2);
    b->addStation(B1,C1);
    b->addStation(B2,C2);
    b->addStation(B3,C3);
    b->addStation(B4,C4);
    b->addStation(B5,C5);
    b->addStation(B6,C6);
    b->addStation(B7,C7);
    b->addStation(B8,C8);
    b->addStation(B9,C9);

    b->addBus(A1,D1);
    b->addBus(A2,D2);
    b->addBus(A3,D3);
    b->addBus(A4,D4);
    b->addBus(A5,D5);
    b->addBus(A6,D6);
    b->addBus(A7,D7);
    b->addBus(A8,D8);
    b->addBus(A9,D9);
    b->addBus(A10,D10);

    b->Addpass(P1);
    b->Addpass(P2);
}

int main() {
BRTS Brts("Hubli");
while(1) {
    int ch;
    cout << "===========================" << endl;
    cout << "   Welcome to BRTS Hubli   " << endl;
    cout << "===========================" << endl;
    cout << "1. Start BRTS Simualtion" << endl;
    cout << "2. Display Buses" << endl;
    cout << "3. Display Stations" << endl;
    cout << "4. Display All Employees" << endl;
    cout << "5. Display All Passengers" << endl;
    cout << "6. Add Buses" << endl;
    cout << "7. Add Bus Station" << endl;
    cout << "8. Add Passenger" << endl;
    cout << "9. Buy Bus Pass for Passenger" << endl;
    cout << "10. Load Prebuilt Brts System" << endl;
    cout << "11. Show Fares Between Source and Destination" << endl;
    cout << "12. Exit" << endl;
    cout << "===========================" << endl;
    cout << "Enter Choice:";
    cin >> ch;
    switch(ch) {
    case 1:
        Brts.simulatePerson();
        break;
    case 2:
        Brts.printBuses();
        break;
    case 3:
        Brts.printStations();
        break;
    case 4:
        Brts.printEmplyee();
        break;
    case 5:
        Brts.printPass();
        break;
    case 6:
        Brts.addBus();
        break;
    case 7:
        Brts.addStation();
        break;
    case 8:
        Brts.Addpass();
        break;
    case 9:
        Brts.buyBuspass();
        break;
    case 10:
        defualtValues(&Brts);
        break;
    case 11:
        Brts.FindFareBetweenStation();
        break;
    case 12:
        exit(0);
        break;
    default:
        exit(0);
    }
}

return 0;
}
