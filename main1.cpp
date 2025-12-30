#include<iostream>
#include<string>
#include<vector>
using namespace std;
class ICustomer{
    public:
    virtual void update(string message)=0;
};
class ConcreteCustomer : public ICustomer{
    public:
    void update(string message) override{
        cout<<"Message: "<<message<<endl;
    }
};
class IStore{
    public:
    virtual void addCustomer(ICustomer* customer)=0;
    virtual void removeCustomer(ICustomer* customer)=0;
    virtual void notifyCustomers(string message)=0; 
};
class ConcreteStore: public IStore{
    protected:
    vector<ICustomer*> customers;
    public:
     void addCustomer(ICustomer* customer){
        customers.push_back(customer);
    }
    void removeCustomer(ICustomer* customer){
        for(auto it =customers.begin();it!=customers.end();it++){
            if(*it==customer)customers.erase(it);
        }
    }
     void notifyCustomers(string message){
        for(auto x:customers){
            x->update(message);
        }
     }
};
