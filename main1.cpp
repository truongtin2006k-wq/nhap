#include <iostream>
#include <vector>
#include <exception>
using namespace std;
class Product
{
protected:
    int id;
    string name;
    double price;

public:
    Product(int id, string name, double price) : id(id), name(name), price(price) {}
    double getPrice()
    {
        return price;
    }
    int getId()
    {
        return id;
    }
    virtual void displayInfo()
    {
        cout << "Id: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << price << endl;
    }
};
class Book : public Product
{
public:
    Book(int id, string name, double price) : Product(id, name, price) {}
    void displayInfo() override
    {
        cout << "This is a Book." << endl;
        Product::displayInfo();
    }
};
class Electronics : public Product
{
public:
    Electronics(int id, string name, double price) : Product(id, name, price) {}
    void displayInfo() override
    {
        cout << "This is an Electronic item." << endl;
        Product::displayInfo();
    }
};
class Clothing : public Product
{
public:
    Clothing(int id, string name, double price) : Product(id, name, price) {}
    void displayInfo() override
    {
        cout << "This is a Clothing item." << endl;
        Product::displayInfo();
    }
};
class DuplicateIdException : public exception
{
public:
    const char *what() const throw()
    {
        return "Duplicate Product ID Exception";
    }
};
class ProductNotFoundException : public exception
{
public:
    const char *what() const throw()
    {
        return "Product Not Found Exception";
    }
};

class ProductCatalog
{
private:
    vector<Product *> products;

public:
    void addProduct(Product *p)
    {
        for (auto prod : products)
        {
            if (prod->getId() == p->getId())
            {
                throw DuplicateIdException();
            }
        }
        products.push_back(p);
    }
    Product *removeProduct(int id)
    {
        for (auto it = products.begin(); it != products.end(); ++it)
        {
            if ((*it)->getId() == id)
            {
                Product *temp = *it;
                products.erase(it);
                return temp;
            }
        }
        throw ProductNotFoundException();
    }
    void displayAll()
    {
        for (auto prod : products)
        {
            prod->displayInfo();
            cout << "          -----------------" << endl;
        }
    }
    vector<Product *> getCheapProducts(double maxPrice)
    {
        vector<Product *> cheapProducts;
        for (auto prod : products)
        {
            if (prod->getPrice() < maxPrice)
                cheapProducts.push_back(prod);
        }
        return cheapProducts;
    }
};
class StoreManager
{
private:
    static StoreManager *instance;
    ProductCatalog catalog;
    StoreManager() {}

public:
    static StoreManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new StoreManager();
            return instance;
        }
        return instance;
    }
    StoreManager(const StoreManager &) = delete;
    StoreManager &operator=(const StoreManager &) = delete;
    ProductCatalog &getCatalog()
    {
        return catalog;
    }
};
class DiscountStrategy
{
public:
    virtual double apply(double total) = 0;
    DiscountStrategy() {}
};
class NoDiscount : public DiscountStrategy
{
public:
    double apply(double total) override
    {
        return total;
    }
};
class MemberDiscount : public DiscountStrategy
{
public:
    double apply(double total) override
    {
        return total * 0.95;
    }
};
class VipDiscount : public DiscountStrategy
{
public:
    double apply(double total) override
    {
        return total * 0.80;
    }
};
class ShoppingCart
{
private:
    vector<Product *> items;
    DiscountStrategy *strategy;

public:
    ShoppingCart() {}
    void addItem(Product *p)
    {
        items.push_back(p);
    }
    void setStrategy(DiscountStrategy *s)
    {
        strategy = s;
    }
    double calculateTotal()
    {
        double total = 0;
        for (auto item : items)
            total += item->getPrice();
        total = strategy->apply(total);
        return total;
    }
};
StoreManager *StoreManager::instance = nullptr;
int main()
{
    try
    {

        StoreManager *manager = StoreManager::getInstance();
        ProductCatalog &catalog = manager->getCatalog();
        catalog.addProduct(new Book(1, "C++ Programming", 29.99));
        catalog.addProduct(new Electronics(2, "Smartphone", 499.99));
        catalog.addProduct(new Clothing(3, "Jeans", 39.99));
        catalog.displayAll();
        catalog.removeProduct(2);
        catalog.displayAll();
        vector<Product *> cheapProducts = catalog.getCheapProducts(50.0);
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    ShoppingCart cart;
    cart.addItem(new Book(1, "C++ Programming", 29.99));
    cart.addItem(new Clothing(3, "Jeans", 39.99));
    cart.setStrategy(new VipDiscount());
    cout << "Total: " << cart.calculateTotal() << endl;
}