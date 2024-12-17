#include <iostream>
#include <conio.h>
#include <pqxx/pqxx>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <sstream>
#include <unordered_set> 
#include <string> 
#include "Config.h"
using namespace std;
using namespace pqxx;

class Aspect {

public:

    virtual void switchTrue() = 0;

    virtual void switchFalse() = 0;

    virtual void getStatus() const = 0;

    virtual int getState() const = 0;

    virtual void setState() = 0;

};

class Light : public Aspect {

    bool state;

public:

    Light() : state(false) {}

    Light(const bool& Lstate) : state(Lstate) {}

    void switchTrue() override {
        state = true;
    }

    void switchFalse() override {
        state = false;
    }

    void getStatus() const override {
        if (state) {
            cout << "Light: on\n";
        }
        else {
            cout << "Light: off\n";
        }
    }

    int getState() const override {
        return state;
    }

    void setState() override {
        char a;
        bool flag = true;
        while (flag)
        {
            cout << "Set light state:\n[a]:On\n[s]:Off\n[x]:Return to menu\n\n";
            getStatus();
            a = _getch();
            switch (a) {
            case 'a':
                switchTrue();
                system("cls");
                break;
            case 's':
                switchFalse();
                system("cls");
                break;
            case 'x':
                system("cls");
                flag = false;
                break;
            default:
                system("cls");
                cout << "\nWrong operation!\n";
                break;
            }
        }
        
    }

};

class Thermostat : public Aspect {

    int temperature;

    void switchTrue() override {}

    void switchFalse() override {}

public:

    Thermostat() : temperature(20) {}

    Thermostat(const int& Ttemperature) : temperature(Ttemperature) {}

    void getStatus() const override {
        cout << "Temperature: " << temperature << endl;
    }

    int getState() const override {
        return temperature;
    }

    int getTemperature() const {
        return temperature;
    }
    
    void setState() override {
        char a;
        bool flag = true;
        while (flag)
        {
            cout << "Set temperature:\n[a]:+1\n[s]:-1\n[x]:Return to menu\n\n";
            getStatus();
            a = _getch();
            switch (a) {
            case 'a':
                temperature += 1;
                system("cls");
                break;
            case 's':
                temperature -= 1;
                system("cls");
                break;
            case 'x':
                system("cls");
                flag = false;
                break;
            default:
                system("cls");
                cout << "\nWrong operation!\n";
                break;
            }
        }
    }

};

class SecuritySystem : public Aspect {

    bool state;

public:

    SecuritySystem() : state(false) {}

    SecuritySystem(const bool& Sstate) : state(Sstate) {}

    void switchTrue() override {
        state = true;
    }

    void switchFalse() override {
        state = false;
    }

    void getStatus() const override {
        if (state) {
            cout << "SecuritySystem: Armed" << endl;
        }
        else {
            cout << "SecuritySystem: Disarmed" << endl;
        }
    }

    int getState() const override {
        return state;
    }

    void setState() override {
        char a;
        bool flag = true;
        while (flag)
        {
            cout << "Set SecuritySystem state:\n[a]:Arm\n[s]:Disarm\n[x]:Return to menu\n\n";
            getStatus();
            a = _getch();
            switch (a) {
            case 'a':
                switchTrue();
                system("cls");
                break;
            case 's':
                switchFalse();
                system("cls");
                break;
            case 'x':
                system("cls");
                flag = false;
                break;
            default:
                system("cls");
                cout << "\nWrong operation!\n";
                break;
            }
        }
    }

};

class Curtains : public Aspect {
    bool state;
public:

    Curtains() : state(false) {}

    Curtains(const bool& Cstate) : state(Cstate) {}

    void switchTrue() override {
        state = true;
    }

    void switchFalse() override {
        state = false;
    }

    void getStatus() const override {
        if (state) {
            cout << "Curtains: Raised" << endl;
        }
        else {
            cout << "Curtains: Lowered" << endl;
        }
    }

    int getState() const override {
        return state;
    }

    void setState() override {
        char a;
        bool flag = true;
        while (flag)
        {
            cout << "Set Curtains state:\n[a]:Raise\n[s]:Low\n[x]:Return to menu\n\n";
            getStatus();
            a = _getch();
            switch (a) {
            case 'a':
                switchTrue();
                system("cls");
                break;
            case 's':
                switchFalse();
                system("cls");
                break;
            case 'x':
                system("cls");
                flag = false;
                break;
            default:
                system("cls");
                cout << "\nWrong operation!\n";
                break;
            }
        }
    }

};

class AirConditioner : public Aspect {

    bool state;

public:

    AirConditioner() : state(false) {}

    AirConditioner(const bool& Astate) : state(Astate) {}

    void switchTrue() override {
        state = true;
    }

    void switchFalse() override {
        state = false;
    }

    void getStatus() const override {
        if (state) {
            cout << "AirConditioner: On" << endl;
        }
        else {
            cout << "AirConditioner: Off" << endl;
        }
    }

    int getState() const override {
        return state;
    }

    void setState() override {
        char a;
        bool flag = true;
        while (flag)
        {
            cout << "Set AirConditioner state:\n[a]:On\n[s]:Off\n[x]:Return to menu\n\n";
            getStatus();
            a = _getch();
            switch (a) {
            case 'a':
                switchTrue();
                system("cls");
                break;
            case 's':
                switchFalse();
                system("cls");
                break;
            case 'x':
                system("cls");
                flag = false;
                break;
            default:
                system("cls");
                cout << "\nWrong operation!\n";
                break;
            }
        }
    }

};

class SmartHome {

    map<char,Aspect*> aspects;
    string stateFile;
    

public:

    SmartHome(const string& SHstateFile) : stateFile(SHstateFile) {
        
        ifstream SF(stateFile);
        
        if (!SF.is_open()) {
            cout << "File not found\n";
            aspects['a'] = new Light();
            aspects['d'] = new SecuritySystem();
            aspects['f'] = new Curtains();
            aspects['g'] = new AirConditioner();
            aspects['s'] = new Thermostat();
        }
        else {
            string str;
            string temp;
            
            cout << "State loaded from " << stateFile << endl;
            while (getline(SF, str)) {
                temp = str;
            }
            stringstream ss(temp);
            getline(ss, temp, ' ');
            aspects['a'] = new Light(stoi(temp));
            getline(ss, temp, ' ');
            aspects['d'] = new SecuritySystem(stoi(temp));
            getline(ss, temp, ' ');
            aspects['f'] = new Curtains(stoi(temp));
            getline(ss, temp, ' ');
            aspects['g'] = new AirConditioner(stoi(temp));
            getline(ss, temp, ' ');
            aspects['s'] = new Thermostat(stoi(temp));
            SF.close();
        }
        
        

    }

    void menu() {
        char a;
        
        while (true)
        {
            
            cout << "\nCurrent state:\n";
            getStatus();
            cout << "\nChoose operation:\n[a]:Control Light\n[s]:Control Thermostat\n[d]:Control Security System\n[f]:Control Curtains\n[g]:Control Air Conditioner\n[w]:Save state\n[x]:Exit SmartHome";

            a = _getch();
            if (a == 'x') {
                system("cls");
                cout << "Goodbye!\n";
                saveState();
                exit(0);
            }
            else if (a == 'w') {
                system("cls");
                saveState();
            }
            else if (aspects.contains(a)) {
                system("cls");
                aspects[a]->setState();
            } else {
                system("cls");
                cout << "Wrong operation!\n";
            }
        
        }
    }

    void getStatus() {
        for (auto aspect : aspects)
        {
            aspect.second->getStatus();
        }
    }

    void saveState() {
        ofstream SF(stateFile, ios::app);

        if (SF.is_open()) {
            for (auto& aspect : aspects)
            {
                SF << aspect.second->getState() << " ";
            }
            SF << endl;
            
            cout << "State saved in " << stateFile << endl;
        }
        else {
            cout << "Saving failed!\n";
        }
        SF.close();
        
        
    }

};

class database {
private:
    string myconfig;
    
public:
    
    database(const string& Dmyconfig) : myconfig(Dmyconfig) {}

    static vector<vector<string>> loadCSV(const string& Dloadfile) {
        ifstream in(Dloadfile);
        if (in.is_open()) {
            string temp;
            vector<vector<string>> a;
            while (getline(in, temp)) {
                stringstream ss(temp);
                vector<string> b;
                while (getline(ss, temp, ',')) {
                    temp.erase(remove(temp.begin(), temp.end(), '\0'), temp.end());
                    b.push_back(temp);
                }
                a.push_back(b);
            }
            in.close();
            return a;
        }
        else {
            cout << "File not loaded!" << endl;
        }
    }

    void insertsales(const string& Dloadfile) {
        connection C(myconfig);
        
        vector<vector<string>> a = loadCSV(Dloadfile);
        for (int i = 1; i < a.size() - 1; i++)
        {
            string str;
            str = "INSERT INTO sales_fact VALUES (" + a[i][0] + ", '" + a[i][1] + "', " + a[i][2] + ", " + a[i][3] + ", " + a[i][4] + ", " + a[i][5] + ") ON CONFLICT DO NOTHING;";
            work W(C);
            W.exec(str);
            
            W.commit();
        }
    }

    void insertproducts(const string& Dloadfile) {
        connection C(myconfig);
       
        vector<vector<string>> a = loadCSV(Dloadfile);
        for (int i = 1; i < a.size() - 1; i++)
        {
            string str;
            str = "INSERT INTO products_dim VALUES (" + a[i][0] + ", '" + a[i][1] + "', '" + a[i][2] + "', " + a[i][3] + ") ON CONFLICT DO NOTHING;";
            work W(C);
            W.exec(str);
            
            W.commit();
        }

    }

    void insertcustomers(const string& Dloadfile) {
        connection C(myconfig);

        vector<vector<string>> a = loadCSV(Dloadfile);
        for (int i = 1; i < a.size() - 1; i++)
        {
            string str;
            str = "INSERT INTO customers_dim VALUES (" + a[i][0] + ", '" + a[i][1] + "', '" + a[i][2] + "') ON CONFLICT DO NOTHING;";
            work W(C);
            W.exec(str);

            W.commit();
        }

    }

    static void showvector(vector<vector<string>> a) {
        for (vector<string>& r : a) {
            for (string& res : r) {
                cout << res << endl;
            }
        }
    }


    void saleamount() {
        connection C(myconfig);

        
       cout << "Category total sales\n";
       string str;
       str = "SELECT products_dim.category, SUM(sales_fact.amount) AS total_sales  FROM sales_fact JOIN products_dim ON sales_fact.product_id = products_dim.product_id  GROUP BY products_dim.category  ORDER BY total_sales DESC;";
       work W(C);
       result res = W.exec(str);
       for (auto r : res) {
           for (auto d : r) {
               cout << d.c_str() << " ";
           }
           cout << endl;
       }
       W.commit();
       cout << endl;
       
        
    }

    void custregcount() {
        connection C(myconfig);
        cout << "Sales count region\n";
        string str;
        str = "SELECT COUNT(sales_fact.sale_id) AS number_of_sales, customers_dim.region FROM sales_fact JOIN customers_dim ON sales_fact.customer_id = customers_dim.customer_id GROUP BY customers_dim.region ORDER BY number_of_sales DESC;";
        work W(C);
        result res = W.exec(str);
       
        for (auto r : res) {
            
            cout << r[0].c_str() << " " << (r[1]).c_str() << endl;
        }
        W.commit();
        cout << endl;
        
        

    }
    void avgmonth() {
        connection C(myconfig);
        string str;
        cout << "Year month avarge check\n";
        str = "SELECT time_dim.year, time_dim.month, AVG(sales_fact.amount) AS average_ticket FROM sales_fact JOIN time_dim ON EXTRACT(YEAR FROM sales_fact.sale_date) = time_dim.year AND EXTRACT(MONTH FROM sales_fact.sale_date) = time_dim.month GROUP BY time_dim.year, time_dim.month ORDER BY time_dim.year, time_dim.month;";
        work W(C);
        result res = W.exec(str);

        for (auto r : res) {
            for (auto d : r) {
                cout << to_string(d.c_str()) << " ";
            }
            cout << endl;
        }
        W.commit();
        cout << endl;



    }

    
};





int main()
{
    database mydb(config);
    
    mydb.insertproducts("C:\\Users\\nikol\\Desktop\\products.csv");
    mydb.insertcustomers("C:\\Users\\nikol\\Desktop\\customers.csv");
    mydb.insertsales("C:\\Users\\nikol\\Desktop\\sales.csv");
    
    mydb.saleamount();

    mydb.custregcount();

    mydb.avgmonth();
   
}


