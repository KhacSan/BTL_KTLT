#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

typedef struct thoiGian {
	string ngayThangNam;
	int gioDen;
	int phutDen;
	int gioVe;
	int phutVe;
}ThoiGian;

typedef struct nhanvien{
	string ho;
	string ten;
	string donVi;
	string chucVu;
	string ngaySinh;
	string queQuan;
	string diaChi;
	string email;
	string sdt;
	string ngayBatDauLamViec;
	vector <ThoiGian> DS_ThoiGianLamViec;
}NhanVien;

//đọc thời gian làm việc của 1 nhân viên
void DocThoiGianLamViec(ifstream &input,ThoiGian &ThoiGianLamViec) {
	getline(input, ThoiGianLamViec.ngayThangNam,',');
	input >> ThoiGianLamViec.gioDen;
	input.seekg(1,1); //dich con tro chi vi 1 byte
	input >> ThoiGianLamViec.phutDen;
	input.seekg(1, 1);
	input >> ThoiGianLamViec.gioVe;
	input.seekg(1, 1);
	input >> ThoiGianLamViec.phutVe;
}

// so sánh 2 ki tu dau tien cua 2 chuoi chuỗi 
int nemcmp(string str1, string str2) {
	for (int i = 0; i < 2; i++)
	{
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	return 0;
}


//đọc thông tin 1 nhân viên từ file
void DocThongTinMotNhanVien(ifstream &input,NhanVien &nhanvien) {
	string str;
	int n = 0,count =0;
	getline(input,str);// doc vào dòng đâu tiên - mã nhân viên
	getline(input, nhanvien.ho);
	getline(input, nhanvien.ten);
	getline(input, nhanvien.donVi);
	getline(input, nhanvien.chucVu);
	getline(input, nhanvien.ngaySinh);
	getline(input, nhanvien.queQuan);
	getline(input, nhanvien.diaChi);
	getline(input, nhanvien.email);
	getline(input, nhanvien.sdt);
	getline(input, nhanvien.ngayBatDauLamViec);

	string temp;
	int vitri = input.tellg();// lay vi tri hien tai cua con tro
	while (true)
	{
		
		if (input.eof()) break;
		getline(input, temp);
		if(nemcmp(temp, "NV") == 0 ) break;
		n++;
	}

	// dich chuyen con tro den vi tri = vitri
	input.seekg(vitri, ios::beg);
	ThoiGian thoiGianLamViec;

	while (count < n )
	{
		DocThoiGianLamViec(input, thoiGianLamViec);
		getline(input, temp);
		nhanvien.DS_ThoiGianLamViec.push_back(thoiGianLamViec);
		count++;
	}

}

void DocFile(ifstream &input, vector <NhanVien> &ds_NhanVien) {

	while (input.eof() == false)
	{
		NhanVien nhanvien;
		DocThongTinMotNhanVien(input, nhanvien);
		ds_NhanVien.push_back(nhanvien);
	}
	
 }

void xuatThoiGian(ThoiGian thoiGian) {
	cout << "Ngay : " << thoiGian.ngayThangNam << "," << thoiGian.gioDen << ":" << thoiGian.phutDen << "," 
		 << thoiGian.gioVe << ":" << thoiGian.phutVe << endl;
}

void xuatThongTinMotNhanVien(NhanVien nhanvien) {
	
	//cout << "Thong tin nhan vien:" << endl;
	cout << "Ho: " << nhanvien.ho << endl;
	cout << "Ten: " << nhanvien.ten << endl;
	cout << "Don vi: " << nhanvien.diaChi << endl;
	cout << "Chuc vu: " << nhanvien.chucVu << endl;
	cout << "Ngay sinh: " << nhanvien.ngaySinh << endl;
	cout << "Que quan: " << nhanvien.queQuan << endl;
	cout << "Dia chi: " << nhanvien.diaChi << endl;
	cout << "Email: " << nhanvien.email << endl;
	cout << "SDT: " << nhanvien.sdt << endl;
	cout << "Ngay bat dau lam viec: " << nhanvien.ngayBatDauLamViec << endl;

	for (int i = 0; i < nhanvien.DS_ThoiGianLamViec.size(); i++) {
		xuatThoiGian(nhanvien.DS_ThoiGianLamViec[i]);
	}
}

void display(vector <NhanVien> ds_NhanVien) {
	for (int i = 0; i < ds_NhanVien.size(); i++) {
		xuatThongTinMotNhanVien(ds_NhanVien[i]);
	}
}

int main()
{
	ifstream input;
	input.open("NhanVien.txt", ios_base::in);
	vector <NhanVien> ds_NhanVien;
	DocFile(input, ds_NhanVien);
	display(ds_NhanVien);
	input.close();
	system("pause");
	return 0;
}