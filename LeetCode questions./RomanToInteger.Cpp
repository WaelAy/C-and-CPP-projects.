/*leet code roman to integer solution faster than 91% of submits and takes less size than 89%*/


int getLetterValue(char letter) {
	switch (letter)
	{
	case 'I':
		return 1;
	case 'V':
		return 5;
	case 'X':
		return 10;
	case 'L':
		return 50;
	case 'C':
		return 100;
	case 'D':
		return 500;
	case 'M':
		return 1000;
	default:
		return 0;
	}
}

int romanToInt(string s) {
	int length = s.length(),answer = 0;
	for (int i = 0; i < length; i++) {
		int  local = 0;
		int next = 0;
		int curr = getLetterValue(s[i]);
		if (i + 1 != length) {
			next = getLetterValue(s[i + 1]);
		}
		if (length - i > 0) {
			
			if (curr < next) {
				local += curr;
				local -= local * 2;
				answer += local;
				local = 0;
			}
			else if (curr == next) {
				local += curr;
			}
			else if (curr > next) {
				answer += curr;
			}
		}
		answer += local;
	}
	return answer;
}

int main() {


	cout<< romanToInt("LVIII")<< endl;


	return 0;
}
