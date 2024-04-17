# Game rắn săn mồi tài xỉu(Snake)
# Mô tả
- Game rắn săn mồi được viết bằng ngôn ngữ lập trình C.
- Thư viện sử dụng `winbgim.h`
- Sử dụng chức năng điều khiển bằng chuột và bàn phím.
- Khi người rắn ăn được mồi, người chơi sẽ phải đặt cược tài hoặc xỉu, nếu thắng cược, rắn sẽ tăng độ dài bằng với số điểm cược và ngược lại nếu cược thua

# Tính năng
- [x] Lưu điểm cao và tên người chơi
- [x] Play/Pause trong khi chơi game
- [x] Đã sửa lỗi xuất hiện trong video
- [x] Thêm tính năng điều khiển bằng chuột
- [x] Thêm file setup trong Release
- [x] Âm thanh sống động

# Cài đặt
Tải file graphics-lib-devC.zip tại repo này về và giải nén, tiến hành

1. Copy:

– file libbgi.a vào thư mục lib (thường là C:\Program Files\Dev-Cpp\MinGW32\lib)

– file winbgim.h và graphics.h vào thư mục include (thường là C:\Program Files\Dev-Cpp\MinGW32\include)

– 2 file 6-ConsoleAppGraphics.template và file ConsoleApp_cpp_graph.txt vào thư mục Templates (thường là C:\Program Files\Dev-Cpp\Templates)

Nếu bạn dùng win 64 bit thì hãy download bản 32 bit về cài bình thường và copy các file như trên nhưng vào thư mục từ C:Program Files (x86)Dev-Cpp…

Xem thêm tại đây: https://cachhoc.net/2013/10/03/cc-do-hoa-trong-dev-c/


2. Đi tới Menu project > project options > parameters and type "-lwinmm" in the LINKER section. Cái này để DevC có thể play audio của game.
