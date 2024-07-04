#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

map<string, int> identifiers;

bool is_identifier(const string& str) {
  return str.size() > 0 && isalpha(str[0]);
}

bool is_int_const(const string& str) {
  return str.size() > 0 && isdigit(str[0]);
}

bool parse_program(const string& input) {
  stringstream ss(input);
  string token;
  ss >> token;
  if (token != "var") {
    cout << "Invalid program: missing 'var' declaration" << endl;
    return false;
  }

  vector<string> var_list;
  while (ss >> token) {
    if (!is_identifier(token)) {
      cout << "Invalid variable name: " << token << endl;
      return false;
    }
    var_list.push_back(token);
  }

  for (const string& var : var_list) {
    identifiers[var] = 0;
  }

  while (ss >> token) {
    if (!parse_operator(ss)) {
      return false;
    }
  }

  return true;
}

bool parse_operator(stringstream& ss) {
  string token;
  ss >> token;

  if (is_identifier(token)) {
    return parse_assignment_operator(ss, token);
  } else if (token == "case") {
    return parse_case_operator(ss);
  } else {
    cout << "Invalid operator: " << token << endl;
    return false;
  }
}

bool parse_assignment_operator(stringstream& ss, const string& var) {
  string token;
  ss >> token;
  if (token != ":=") {
    cout << "Invalid assignment operator: " << token << endl;
    return false;
  }

  string expr;
  ss >> expr;
  if (!is_identifier(expr) && !is_int_const(expr)) {
    cout << "Invalid expression in assignment operator: " << expr << endl;
    return false;
  }

  identifiers[var] = stoi(expr);
  return true;
}

bool parse_case_operator(stringstream& ss) {
  string token;
  ss >> token;
  if (!is_identifier(token)) {
    cout << "Invalid expression in case operator: " << token << endl;
    return false;
  }

  string expr = token;

  ss >> token;
  if (token != "of") {
    cout << "Invalid case operator: missing 'of'" << endl;
    return false;
  }

  while (ss >> token) {
    if (!parse_alternative(ss)) {
      return false;
    }
  }

  return true;
}

bool parse_alternative(stringstream& ss) {
  string token;
  ss >> token;
  if (!is_int_const(token)) {
    cout << "Invalid constant in alternative: " << token << endl;
    return false;
  }

  int value = stoi(token);

  ss >> token;
  if (token != ":") {
    cout << "Invalid alternative: missing ':'" << endl;
    return false;
  }

  if (!parse_operator(ss)) {
    return false;
  }

  return true;
}

int main() {
  string input;
  cout << "Enter a Pascal program: ";
  getline(cin, input);

  if (parse_program(input)) {
    cout << "Program successfully parsed" << endl;
  } else {
    cout << "Program parsing failed" << endl;
  }

  return 0;
}
