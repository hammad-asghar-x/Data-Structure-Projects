#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct order_node
{
    string order_details;
    order_node* next;
};

struct Customer
{
    int customer_id;
    string name;
    string contact_info;
    order_node* order_history;
};

struct customer_node
{
    Customer customer_data;
    customer_node* next;
};

struct menu_item
{
    string item_name;
    double price;
    menu_item* left;
    menu_item* right;
};

struct Employee
{
    int emp_id;
    string name;
    string position;
};

struct inventory_item
{
    int item_id;
    string name;
    int quantity;
    double price;
};

class Customer_Management
{
private:
    customer_node* head;

public:
    Customer_Management() : head(nullptr) {}

    void add_customer(int id, const string& name, const string& contactInfo)
    {
        customer_node* newNode = new customer_node;
        newNode->customer_data = { id, name, contactInfo, nullptr };
        newNode->next = head;
        head = newNode;
        cout << "Customer added successfully." << endl;
    }

    void view_customer(int id)
    {
        customer_node* temp = head;
        while (temp != nullptr)
        {
            if (temp->customer_data.customer_id == id)
            {
                cout << "Customer ID: " << temp->customer_data.customer_id << endl;
                cout << "Name: " << temp->customer_data.name << endl;
                cout << "Contact Info: " << temp->customer_data.contact_info << endl;
                cout << "Order History:" << endl;
                order_node* orderTemp = temp->customer_data.order_history;
                if (orderTemp == nullptr)
                {
                    cout << "  No orders yet." << endl;
                }
                else
                {
                    while (orderTemp != nullptr)
                    {
                        cout << "  - " << orderTemp->order_details << endl;
                        orderTemp = orderTemp->next;
                    }
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Customer not found." << endl;
    }

    void add_order_history(int id, const string& orderDetails)
    {
        customer_node* temp = head;
        while (temp != nullptr)
        {
            if (temp->customer_data.customer_id == id)
            {
                order_node* newOrder = new order_node;
                newOrder->order_details = orderDetails;
                newOrder->next = temp->customer_data.order_history;
                temp->customer_data.order_history = newOrder;
                cout << "Order added successfully." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Customer not found." << endl;
    }
};

class Menu_Management
{
private:
    menu_item* root;

    menu_item* insert(menu_item* node, const string& itemName, double price)
    {
        if (node == nullptr)
        {
            node = new menu_item{ itemName, price, nullptr, nullptr };
            return node;
        }
        if (itemName < node->item_name)
            node->left = insert(node->left, itemName, price);
        else if (itemName > node->item_name)
            node->right = insert(node->right, itemName, price);
        else
            cout << "Item already exists!" << endl;
        return node;
    }

    menu_item* search(menu_item* node, const string& itemName)
    {
        if (node == nullptr || node->item_name == itemName)
            return node;
        if (itemName < node->item_name)
            return search(node->left, itemName);
        return search(node->right, itemName);
    }

    void inorder_traversal(menu_item* node)
    {
        if (node == nullptr)
            return;
        inorder_traversal(node->left);
        cout << "Item: " << node->item_name << ", Price: $" << node->price << endl;
        inorder_traversal(node->right);
    }

public:
    Menu_Management() : root(nullptr) {}

    void add_item(const string& itemName, double price)
    {
        root = insert(root, itemName, price);
        cout << "Menu item added successfully." << endl;
    }

    void search_item(const string& itemName)
    {
        menu_item* result = search(root, itemName);
        if (result != nullptr) {
            cout << "Item found: " << result->item_name << ", Price: $" << result->price << endl;
        }
        else
        {
            cout << "Item not found." << endl;
        }
    }

    void display_Menu()
    {
        if (root == nullptr)
        {
            cout << "Menu is empty." << endl;
            return;
        }
        cout << "Menu Items:" << endl;
        inorder_traversal(root);
    }
};

class Employee_Management
{
private:
    unordered_map<int, Employee> employeeTable;

public:
    void add_employee(int id, const string& name, const string& position)
    {
        Employee emp = { id, name, position };
        employeeTable[id] = emp;
        cout << "Employee added successfully." << endl;
    }

    void view_employee(int id)
    {
        if (employeeTable.find(id) != employeeTable.end())
        {
            Employee emp = employeeTable[id];
            cout << "Employee ID : " << emp.emp_id << endl;
            cout << "Name        : " << emp.name << endl;
            cout << "Position    : " << emp.position << endl;
        }
        else
        {
            cout << "Employee not found." << endl;
        }
    }

    void view_all_employees()
    {
        if (employeeTable.empty())
        {
            cout << "No employees found." << endl;
            return;
        }
        cout << "All the Employess in the Cafe are " << endl;
        cout << "----------------------------------" << endl;

        for (const auto& entry : employeeTable)
        {
            const Employee& emp = entry.second;  
            cout << "Employee ID : " << emp.emp_id << endl;
            cout << "Name        : " << emp.name << endl;
            cout << "Position    : " << emp.position << endl;
            cout << "-----------------------------" << endl;
        }
    }

};

class Inventory_Management
{
private:
    unordered_map<int, inventory_item> inventoryTable;

public:
    void add_item(int id, const string& name, int qty, double price)
    {
        inventory_item item = { id, name, qty, price };
        inventoryTable[id] = item;
        cout << "Item added successfully." << endl;
    }

    void view_item(int id)
    {
        if (inventoryTable.find(id) != inventoryTable.end())
        {
            inventory_item item = inventoryTable[id];
            cout << "Item ID  : " << item.item_id << endl;
            cout << "Name     : " << item.name << endl;
            cout << "Quantity : " << item.quantity << endl;
            cout << "Price    : $" << item.price << endl;
        }
        else
        {
            cout << "Item not found." << endl;
        }
    }

    void view_all_item()
    {
        if (inventoryTable.empty())
        {
            cout << "No employees found." << endl;
            return;
        }
        cout << "All the Items in the Cafe are " << endl;
        cout << "------------------------------" << endl;
        for (const auto& entry : inventoryTable)
        {
            const inventory_item& item = entry.second;
            cout << "Item ID  : " << item.item_id << endl;
            cout << "Name     : " << item.name << endl;
            cout << "Quantity : " << item.quantity << endl;
            cout << "Price    : $" << item.price << endl;
            cout << "-----------------------------" << endl;
        }
    }

    void update_quantity(int id, int newQty)
    {
        if (inventoryTable.find(id) != inventoryTable.end())
        {
            inventoryTable[id].quantity += newQty;
            cout << "Quantity updated successfully." << endl;
        }
        else
        {
            cout << "Item not found." << endl;
        }
    }
};

int main()
{
    Customer_Management customer;
    Menu_Management menu;
    Employee_Management employee;
    Inventory_Management inventory;


    int choice;
    do
    {
        system("CLS");
        cout << "Cafe Management System Menu:" << endl;
        cout << "1. Customer Management" << endl;
        cout << "2. Menu Management" << endl;
        cout << "3. Employee Management" << endl;
        cout << "4. Inventory Management" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int c_choice;
            do
            {
                system("CLS");
                cout << "Customer Management Menu:" << endl;
                cout << "1. Add Customer" << endl;
                cout << "2. View Customer" << endl;
                cout << "3. Add Order to Customer" << endl;
                cout << "4. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> c_choice;

                if (c_choice == 1)
                {
                    int id;
                    string name, info;
                    cout << "Enter Customer ID: ";
                    cin >> id;
                    cout << "Enter Customer Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Contact Info: ";
                    getline(cin, info);
                    customer.add_customer(id, name, info);
                    system("pause");
                }
                else if (c_choice == 2)
                {
                    int id;
                    cout << "Enter Customer ID to view: ";
                    cin >> id;
                    customer.view_customer(id);
                    system("pause");
                }
                else if (c_choice == 3)
                {
                    int id;
                    string order_details;
                    cout << "Enter Customer ID to add order: ";
                    cin >> id;
                    cout << "Enter Order Details: ";
                    cin.ignore();
                    getline(cin, order_details);
                    customer.add_order_history(id, order_details);
                    system("pause");
                }
            } while (c_choice != 4);
            break;
        }
        case 2:
        {
            int m_choice;
            do {
                system("CLS");
                cout << "Menu Management Menu:" << endl;
                cout << "1. Add Menu Item" << endl;
                cout << "2. Search Menu Item" << endl;
                cout << "3. Display Menu" << endl;
                cout << "4. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> m_choice;

                if (m_choice == 1)
                {
                    string name;
                    double price;
                    cout << "Enter Menu Item Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Price: ";
                    cin >> price;
                    menu.add_item(name, price);
                    system("pause");
                }
                else if (m_choice == 2)
                {
                    string name;
                    cout << "Enter Menu Item Name to search: ";
                    cin.ignore();
                    getline(cin, name);
                    menu.search_item(name);
                    system("pause");
                }
                else if (m_choice == 3)
                {
                    menu.display_Menu();
                    system("pause");
                }
            } while (m_choice != 4);
            break;
        }
        case 3:
        {
            int e_choice;
            do
            {
                system("CLS");
                cout << "Employee Management Menu:" << endl;
                cout << "1. Add Employee" << endl;
                cout << "2. View Employee" << endl;
                cout << "3. View All Employee" << endl;
                cout << "4. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> e_choice;

                if (e_choice == 1)
                {
                    int id;
                    string name, position;
                    cout << "Enter Employee ID: ";
                    cin >> id;
                    cout << "Enter Employee Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Position: ";
                    getline(cin, position);
                    employee.add_employee(id, name, position);
                    system("pause");
                }
                else if (e_choice == 2)
                {
                    int id;
                    cout << "Enter Employee ID to view: ";
                    cin >> id;
                    employee.view_employee(id);
                    system("pause");
                }
                else if (e_choice == 3)
                {
                    employee.view_all_employees();
                    system("pause");
                }
            } while (e_choice != 4);
            break;
        }
        case 4:
        {
            int i_choice;
            do
            {
                system("CLS");
                cout << "Inventory Management Menu:" << endl;
                cout << "1. Add Item" << endl;
                cout << "2. View Item" << endl;
                cout << "3. View All Item" << endl;
                cout << "4. Update Item Quantity" << endl;
                cout << "5. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> i_choice;

                if (i_choice == 1)
                {
                    int id, quantity;
                    string name;
                    double price;
                    cout << "Enter Item ID: ";
                    cin >> id;
                    cout << "Enter Item Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Quantity: ";
                    cin >> quantity;
                    cout << "Enter Price: ";
                    cin >> price;
                    inventory.add_item(id, name, quantity, price);
                    system("pause");
                }
                else if (i_choice == 2)
                {
                    int id;
                    cout << "Enter Item ID to view: ";
                    cin >> id;
                    inventory.view_item(id);
                    system("pause");
                }
                else if (i_choice == 3)
                {
                    inventory.view_all_item();
                    system("pause");
                }
                else if (i_choice == 4)
                {
                    int id, new_quantity;
                    cout << "Enter Item ID to update quantity: ";
                    cin >> id;
                    cout << "Enter New Quantity: ";
                    cin >> new_quantity;
                    inventory.update_quantity(id, new_quantity);
                    system("pause");
                }
            } while (i_choice != 5);
            break;
        }
        case 5:
            cout << "Exiting the system. Thank you!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}