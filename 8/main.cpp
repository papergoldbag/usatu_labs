#include <iostream>
#include <string>
#include <sstream>

#define BIG_INTEGER_SIZE 128

using namespace std;

class WrongInputBigIntegerException : public std::exception {
    [[nodiscard]] const char *what() const noexcept override {
        return "You entered an incorrect string when initializing a big integer.";
    }
};

class DivisionBigIntegerException : public std::exception {
    [[nodiscard]] const char *what() const noexcept override {
        return "It is impossible to divide this two big integers.";
    }
};

class BigInteger {
private:
    static const int max_length = BIG_INTEGER_SIZE;
    int digits[max_length]{};
    bool positive{};

    bool is_zero() {
        return size() == 1 && digits[max_length - 1] == 0;
    }

    void normalize() {
        if (size() == 1 && digits[max_length - 1] == 0)
            positive = true;

        for (int i = 0; i < max_length - 1; ++i) {
            if (digits[i] != 0 && digits[i] != -1)
                break;
            digits[i] = -1;
        }
    }

    int size() {
        for (int i = 0; i < max_length; ++i) {
            if (digits[i] != -1)
                return max_length - i;
        }
        return 0;
    }

    void clear() {
        for (int &digit: digits)
            digit = -1;
    }

    void convert_string_to_big_integer(const string &input) {
        int input_size = input.size();
        positive = true;

        for (const auto &item: input) {
            if (item == '-') {
                positive = false;
                continue;
            }

            if (item - 48 < 0 || 9 < item - 48)
                throw WrongInputBigIntegerException();
        }

        int input_pos = !positive, digits_pos = max_length - input_size + !positive;
        while (digits_pos < max_length)
            digits[digits_pos++] = input[input_pos++] - 48;

        digits_pos -= (1 + input_size);
        while (digits_pos >= 0)
            digits[digits_pos--] = -1;
    }

    pair<BigInteger, BigInteger> division(const BigInteger &right) {
        BigInteger result, temp, new_left = *this, new_right = right, ten("10");
        string string_result;

        if (new_right.is_zero())
            throw DivisionBigIntegerException();

        int left_size = new_left.size();
        int right_size = new_right.size();
        for (int i = max_length - left_size; i < max_length; ++i) {
            temp *= ten;
            temp += new_left.digits[i];
            if (temp < new_right)
                continue;
            for (int k = 1; k < 10; ++k) {
                if (temp < (new_right * k)) {
                    string_result += std::to_string(k - 1);
                    temp -= (new_right * (k - 1));
                    break;
                }
            }
        }
        result = string_result.empty() ? "0" : string_result;
        while (result.size() < (left_size - right_size))
            result *= 10;
        return pair(result, temp);
    }

public:

    string to_string() {
        return to_string(*this);
    }

    static string to_string(BigInteger number) {
        string result;
        int i = BigInteger::max_length - number.size();

        if (!number.positive)
            result += '-';

        while (i < BigInteger::max_length)
            result += (std::to_string(number.digits[i++]));

        return result;
    }

    explicit BigInteger(const string &number) {
        clear();
        convert_string_to_big_integer(number.empty() ? "0" : number);
    }

    explicit BigInteger(int number) {
        clear();
        string number_string;
        stringstream ss;
        ss << number;
        ss >> number_string;
        convert_string_to_big_integer(number_string);
    }

    BigInteger() {
        clear();
        convert_string_to_big_integer("0");
    }

    void change_sign() {
        positive = !positive;
    }

    BigInteger &operator=(const BigInteger &right) {
        if (this == &right)
            return *this;

        for (int i = 0; i < max_length; ++i)
            digits[i] = right.digits[i];

        positive = right.positive;
        return *this;
    }

    BigInteger &operator=(const string &right) {
        convert_string_to_big_integer(right);
        normalize();
        return *this;
    }

    bool operator<(const BigInteger &right) {
        BigInteger new_right = right;
        int right_size = new_right.size(), left_size = size();
        if (right.positive == positive) {
            if (right_size != left_size)
                return (right_size > left_size) ^ !positive;
        } else if (right.positive && !positive)
            return true;
        else if (!right.positive && positive)
            return false;

        int i;
        for (i = max_length - left_size; i < max_length && right.digits[i] == digits[i]; ++i);

        if (i >= max_length)
            i--;

        if (positive)
            return digits[i] < right.digits[i];
        else
            return digits[i] > right.digits[i];
    }

    bool operator>(BigInteger &right) const {
        return right < *this;
    }

    bool operator>=(const BigInteger &right) {
        return !(*this < right);
    }

    bool operator<=(BigInteger &right) const {
        return !(right < *this);
    }

    BigInteger operator-(const BigInteger &right) {
        int in_mind = 0, temp_result, temp_left, temp_right;

        BigInteger new_right = right, new_left = *this, result;

        if (new_left.positive && new_right.positive) { // a > 0, b > 0
            if (new_left < new_right) { // a < b
                result = "-1";
                return (new_right - new_left) * result;
            }
        } else if (!new_left.positive && new_right.positive) { // a < 0, b > 0
            result = "-1";
            new_left.positive = true;
            return (new_left + new_right) * result;
        } else if (new_left.positive && !new_right.positive) { // a > 0, b < 0
            new_right.positive = true;
            return new_left + new_right;
        } else if (!new_left.positive && !new_right.positive) { // a < 0, b < 0
            result = "-1";
            new_right.positive = true;
            new_left.positive = true;
            return (new_left - new_right) * result;
        }

        // a > 0, b > 0, a > b
        for (int i = max_length - 1; i >= 0; --i) {

            if (right.digits[i] == -1 && digits[i] == -1) {
                result.digits[i] = -1;
                continue;
            }

            temp_left = digits[i] == -1 ? 0 : digits[i];
            temp_right = right.digits[i] == -1 ? 0 : right.digits[i];

            temp_result = temp_left - temp_right - in_mind;
            if (temp_result < 0) {
                result.digits[i] = temp_result + 10;
                in_mind = 1;
            } else {
                result.digits[i] = temp_result;
                in_mind = 0;
            }
        }

        result.normalize();
        return result;
    }

    BigInteger operator+(const BigInteger &right) {
        int in_mind = 0, temp_result, temp_left, temp_right;

        BigInteger new_right = right, new_left = *this, result;

        if (new_left.positive && !new_right.positive) {
            new_right.positive = true;
            return new_left - new_right;
        } else if (!new_left.positive && new_right.positive) {
            new_left.positive = true;
            return new_right - new_left;
        }

        for (int i = max_length - 1; i >= 0; --i) {

            if (right.digits[i] == -1 && digits[i] == -1 && in_mind == 0) {
                result.digits[i] = -1;
                continue;
            }

            temp_left = digits[i] == -1 ? 0 : digits[i];
            temp_right = right.digits[i] == -1 ? 0 : right.digits[i];

            temp_result = temp_left + temp_right + in_mind;
            result.digits[i] = temp_result % 10;
            in_mind = temp_result / 10;
        }

        result.positive = right.positive;
        result.normalize();
        return result;
    }

    BigInteger operator/(const BigInteger &right) {
        return division(right).first;
    }

    BigInteger operator%(const BigInteger &right) {
        return division(right).second;
    }

    BigInteger operator*(const BigInteger &right) {
        BigInteger result, new_right = right;

        for (int &digit: result.digits)
            digit = 0;

        int left_size = size(), right_size = new_right.size();
        if (left_size < right_size)
            return new_right * *this;

        for (int i = 0; i < left_size; ++i)
            for (int j = 0; j < right_size; ++j)
                result.digits[max_length - i - j - 1] += digits[max_length - i - 1] * right.digits[max_length - j - 1];

        for (int i = 1; i < left_size + right_size; ++i) {
            result.digits[max_length - i - 1] += result.digits[max_length - i] / 10;
            result.digits[max_length - i] %= 10;
        }

        int i = 0;
        while (result.digits[i] == 0 && i < max_length - 1)
            result.digits[i++] = -1;

        result.positive = positive == right.positive;

        result.normalize();
        return result;
    }

    friend ostream &operator<<(ostream &os, BigInteger const &number) {
        return os << to_string(number);
    }

    BigInteger operator+(int right) {
        BigInteger new_right(right);
        return *this + new_right;
    }

    BigInteger operator-(int right) {
        BigInteger new_right(right);
        return *this - new_right;
    }

    BigInteger operator*(int right) {
        BigInteger new_right(right);
        return *this * new_right;
    }

    void operator-=(const BigInteger &right) {
        *this = *this - right;
    }

    void operator+=(const BigInteger &right) {
        *this = *this + right;
    }

    void operator*=(const BigInteger &right) {
        *this = *this * right;
    }

    void operator-=(int right) {
        *this = *this - right;
    }

    void operator+=(int right) {
        *this = *this + right;
    }

    void operator*=(int right) {
        *this = *this * right;
    }
};


void test(const string &string_a, const string &string_b) {
    BigInteger a(string_a), b(string_b);
    cout << "- = { X } = -" << endl
         << "a = " << a << endl
         << "b = " << b << endl
         << "a + b = " << a + b << endl
         << "a - b = " << a - b << endl
         << "b - a = " << b - a << endl
         << "a * b = " << a * b << endl
         << "a < b = " << (a < b ? "true" : "false") << endl
         << "a <= b = " << (a <= b ? "true" : "false") << endl
         << "a > b = " << (a > b ? "true" : "false") << endl
         << "a >= b = " << (a >= b ? "true" : "false") << endl
         << "a / b = " << a / b << endl
         << "b / a = " << b / a << endl
         << "a % b = " << a % b << endl
         << "b % a = " << b % a << endl
         << "- = { X } = -" << endl
         << endl;
    cin.get();
}


int main() {
    test("135624514562345", "2213452");
    test("228133722813371", "727727727727727");
    test("55555555555555555555", "12");
    test("1234", "4321");
    test("9", "9");
    return 0;
}
