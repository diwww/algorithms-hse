#include <string>

const std::string _charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

class Helper
{
public:
	Helper();
	std::string getRandomString(size_t len);
};

Helper::Helper()
{
	srand(time(NULL));
}

std::string Helper::getRandomString(size_t len)
{
	std::string result;
	result.resize(len);

	for (int i = 0; i < len; ++i)
		result[i] = _charset[rand() % _charset.length()];

	return result;
}
