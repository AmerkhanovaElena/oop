#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string ReplaceString(const string& line, const string& soughtString, const string& replacingString)
{
	string result;
    size_t pos = 0;
    size_t foundPos = line.find(soughtString);
    while (foundPos != string::npos)
    {
        result.append(line, pos, foundPos - pos);
        result.append(replacingString);
        pos = foundPos + soughtString.length();
        foundPos = line.find(soughtString, foundPos + soughtString.length());
    }
    result.append(line, pos, line.length() - pos);

	return result;
}

void CopyFileWithStringReplacing(istream& inputFile, ostream& outputFile, const string& soughtString, const std::string& replacingString)
{
	string line;

	while (getline(inputFile, line))
	{
		outputFile << ReplaceString(line, soughtString, replacingString) << "\n";
	}
}

void CopyFileWithoutStringReplacing(istream& inputFile, ostream& outputFile)
{
    string line;

    while (getline(inputFile, line))
    {
        outputFile << line << "\n";
    }
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
        return 1;
    }

    ifstream input;
    input.open(argv[1]);
    if (!input.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading\n";
        return 1;
    }

    ofstream output;
    output.open(argv[2]);
    if (!output.is_open())
    {
        cout << "Failed to open " << argv[2] << " for writing\n";
        return 1;
    }

    string search = argv[3];
    string replace = argv[4];

    if (!search.empty())
    {
        CopyFileWithStringReplacing(input, output, search, replace);
    }
    else
    {
        CopyFileWithoutStringReplacing(input, output);
    }
}