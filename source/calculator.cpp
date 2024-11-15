#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

const double PI = 3.14159265;

void showMenu()
{
    system("clear");
    cout << "Welcome to the Scientific Calculator" << endl;
    cout << "\n--- Scientific Calculator ---\n";
    cout << "1. Basic Arithmetic\n";
    cout << "2. Logarithm\n";
    cout << "3. Antilogarithm\n";
    cout << "4. Trignometry\n";
    cout << "5. Factorial\n";
    cout << "6. Exit\n";
    cout << "Select an option: ";
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

string convertToPostfix(string s)
{
    stack<char> st;
    string postfix = "";
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
            continue;

        if (isdigit(s[i]))
        {
            while (i < s.length() && (isdigit(s[i]) || s[i] == '.'))
            {
                postfix += s[i];
                i++;
            }
            postfix += ' '; // Add space after number
            i--;            // Adjust i as it will be incremented in the for loop
        }
        else if (isOperator(s[i]))
        {
            while (!st.empty() && precedence(st.top()) >= precedence(s[i]))
            {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.push(s[i]);
        }
        else if (s[i] == '(')
        {
            st.push(s[i]);
        }
        else if (s[i] == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.pop(); // Remove the '(' from the stack
        }
    }
    while (!st.empty())
    {
        postfix += st.top();
        postfix += ' ';
        st.pop();
    }

    return postfix;
}

double mathsCalculation(string s)
{
    string postfix = convertToPostfix(s);
    stack<double> st;
    istringstream iss(postfix);
    string token;

    while (iss >> token)
    {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-'))
        {
            st.push(stod(token)); // Convert string to double
        }
        else
        {
            double op2 = st.top();
            st.pop();
            double op1 = st.top();
            st.pop();

            switch (token[0])
            {
            case '+':
                st.push(op1 + op2);
                break;
            case '-':
                st.push(op1 - op2);
                break;
            case '*':
                st.push(op1 * op2);
                break;
            case '/':
                st.push(op1 / op2);
                break;
            case '^':
                st.push(pow(op1, op2));
                break;
            }
        }
    }

    return st.top();
}

double logOfbase()
{
    cout << "Enter the base: ";
    double base;
    cin >> base;
    cout << "Enter the number: ";
    double num;
    cin >> num;

    if (num <= 0 || base <= 0 || base == 1)
    {
        cout << "Invalid input" << endl;
        return -1;
    }
    double result = log(num) / log(base);

    return result;
}

double antiLog()
{
    cout << "Enter the base: ";
    double base;
    cin >> base;
    cout << "Enter the number: ";
    double num;
    cin >> num;

    if (num <= 0 || base <= 0 || base == 1)
    {
        cout << "Invalid input" << endl;
        return -1;
    }
    double result = pow(base, num);

    return result;
}

void trigonometry() {
    int choice2;
    cout << "1. Sine\n";
    cout << "2. Cosine\n";
    cout << "3. Tangent\n";
    cout << "4. Cotangent\n";
    cout << "5. Secant\n";
    cout << "6. Cosecant\n";
    cout << "Select an option: ";
    cin >> choice2;
    double x;
    cout << "Enter the angle in degrees: ";
    cin >> x;
	x = x * PI / 180; // Convert degrees to radians
    switch (choice2)
    {
    case 1:
        cout << "Result: " << sin(x) << endl;
        break;
    case 2:
        cout << "Result: " << cos(x) << endl;
        break;
    case 3:
        cout << "Result: " << tan(x) << endl;
        break;
    case 4:
        cout << "Result: " << 1/tan(x) << endl;
        break;
    case 5:
        cout << "Result: " << 1/cos(x) << endl;
        break;
    case 6:
        cout << "Result: " << 1/sin(x) << endl;
        break;
    default:
        cout << "Invalid choice" << endl;
        break;
    }
    cout << "Press Enter to continue..." << endl;
    cin.ignore();
    cin.ignore();


}

long long factorial(int x)
{
    vector<long long> v(x + 1, -1);
    if (x == 0)
    {
        return 1;
    }
    if (v[x] == -1)
    {
        v[x] = x * factorial(x - 1);
    }

    return v[x];
}

void calculator()
{

    int choice;

    do
    {
        showMenu();
        cin >> choice;

        // Check if the input is not an integer
        if (cin.fail())
        {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
            cout << "Invalid input. Press enter to continue." << endl;
			cin.ignore(); // Ignore the Enter key
            continue; // Skip the rest of the loop and show the menu again
        }

        switch (choice)
        {
        case 1:
        {
            string s;
            cout << "Enter the expression: ";
            cin.ignore();
            getline(cin, s);
            cout << "Result: " << mathsCalculation(s) << endl;
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
        }
        break;
        case 2:
        {
            double result = logOfbase();
            if (result != -1)
            {
                cout << "Result: " << result << endl;
            }
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.ignore();
            
        }
        break;
        case 3:
        {
            double result = antiLog();
            if (result != -1)
            {
                cout << "Result: " << result << endl;
            }
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.ignore();

        }
        break;
        case 4:
			trigonometry();
            
        break;
        case 5:
        {
            int x;
            cout << "Enter the number: ";
            cin >> x;
            cout << "Result: " << factorial(x) << endl;
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.ignore();

        }
        break;
        case 6:
        {
            cout << "Exiting..." << endl;
			cin.ignore();
        }
        break;
        default:
            cout << "Invalid choice" << endl;
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.ignore();

            break;
        }

    } while (choice != 6);

    
}