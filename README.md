# BÀI TẬP LỚN LẬP TRÌNH NÂNG CAO

- Họ và tên: Trần Anh Khoa  
- Mã số sinh viên: 24022806  
- Tên đề tài: Pop Balloon Time — Game nhận dạng glyph phá bóng  

---

## 🎮 Mô tả trò chơi

Pop Balloon Time là trò chơi mini lấy cảm hứng từ game "Magic Touch: Wizard for Hire".  
Người chơi nhập vai pháp sư bảo vệ lâu đài khỏi các quả bóng phép đang rơi.  
Mỗi quả bóng mang một ký tự phép (glyph), và người chơi cần vẽ đúng glyph tương ứng để phá hủy nó.

---

## 🕹️ Cách chơi

- Khi khởi động sẽ hiển thị menu với các nút:  
  - Play Game  
  - Save High Score  
  - Sound ON/OFF(chưa kịp :<) 
  - Quit Game

- Chọn "Play Game" để bắt đầu chơi.

- Trong game:
  - Các quả bóng chứa glyph bay từ dưới lên.
  - Dùng chuột để vẽ glyph ngay trên màn hình.
  - Vẽ đúng → bóng nổ → cộng điểm.
  - Bóng đi quá biên trên màn hình → mất một mạng.
  - Game Over khi hết mạng.

- Có thể tạm dừng bằng nút “PAUSE” ở góc màn hình.

- Sau khi thua: có thể chơi lại hoặc quay về menu.

---

## 🧠 Cơ chế tính điểm

- Mỗi bóng phá được:
  - Combo càng nhiều → điểm càng cao.
  - Điểm = số bóng phá được * số bóng phá được.

- Nếu không phá được bóng:
  - Mất 1 mạng.
  - Combo reset.

---

## ✍️ Nhận dạng glyph (vẽ ký tự)

- Vẽ bằng chuột: mỗi nét được chuyển thành chuỗi hướng (R/L/U/D).
- So khớp thủ công bằng logic trong logic.cpp (không dùng AI).

---

## ⚙️ Cấu trúc mã nguồn

- main.cpp — vòng lặp chính của game.
- graphics.* — hiển thị ảnh, chữ, nút.
- logic.* — xử lý nét vẽ và nhận dạng glyph.
- balloon_entity.* — quản lý bóng phép, di chuyển, nổ.
- menu.*, pause.*, gameover.* — các màn hình tương ứng.
- cloud.* — hiển thị mây bay nền game.
- button.* — xử lý nút cơ bản.
- defs.h — các hằng số như kích thước, vị trí,...
- highscore.txt — lưu điểm cao.

---

## 📁 Thư mục dự án

- ./assets/ — hình ảnh: bóng, nổ, lâu đài, nền, dot vẽ,...
- ./sfx/ — âm thanh (tạm chưa có ).
- highscore.txt — lưu điểm cao nhất.
- README.md — tài liệu mô tả game.

---

## 🛠️ Build & chạy

Yêu cầu:
- SDL2  
- SDL2_image  
- SDL2_ttf  
- SDL2_mixer (tạm chưa có)
## Ngưỡng điểm tự đánh giá: 7.5 
 Lí do: tốn nhiều thử nghiệm cho phương pháp nhận diện nhưng chưa ưng ý và chỉnh chu các phần khác.
