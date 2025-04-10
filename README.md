# ForYouMusicPlayer
Just for you.
### 产品需求文档（PRD）**
#### **项目名称：ForYouMusicPlayer 精致美观的本地音乐播放器**

### **一、项目背景与目标**
#### **1.1 项目背景**
随着用户对本地音乐管理需求的增加，开发一个功能完善、界面美观的本地音乐播放器成为必要。本项目旨在通过Qt5 GUI框架和SQLite数据库，打造一个具有实用性和创新性的本地音乐播放器。

#### **1.2 项目目标**
1. **功能目标**：实现本地音乐文件的添加、播放控制、歌词显示、歌单管理等功能。
2. **用户体验目标**：提供简洁优雅的UI设计，支持自定义背景，提升用户体验。
3. **技术目标**：掌握Qt5多媒体模块和SQLite数据库的使用，提升复杂程序的设计与调试能力。
4. **文档目标**：撰写规范的软件文档，包括使用说明和设计说明。

### **二、功能需求**
#### **2.1 核心功能**
1. **本地音乐管理**
   - 支持添加本地音乐文件（.mp3、.flac、.mpga格式）。
   - 支持通过拖拽文件至主窗口完成音乐添加。
   - 自动过滤非支持格式文件，确保播放器仅处理有效音乐文件。

2. **播放控制**
   - 支持上一曲、下一曲、暂停/播放功能。
   - 支持音量调节和进度条拖动。
   - 支持单曲循环和列表循环播放模式。

3. **歌词显示**
   - 自动加载与歌曲同名的歌词文件（.lrc格式）。
   - 使用正则表达式解析歌词时间戳，实现实时歌词显示。
   - 支持歌词文件编码识别（UTF-8、GBK等），避免乱码问题。

4. **歌单管理**
   - 支持创建、删除歌单。
   - 支持将歌曲添加到歌单或从歌单中删除。
   - 支持双击歌单中的歌曲直接播放。

5. **自定义背景**
   - 支持通过设置界面选择背景图片。
   - 背景图片路径保存至配置文件（.ini），确保下次启动时恢复用户设置。

#### **2.2 高级功能**
1. **数据库管理**
   - 使用SQLite数据库存储音乐信息（歌曲名、歌手、专辑、路径等）。
   - 支持数据库的增删改查操作，确保歌单管理功能的实现。

2. **界面设计**
   - 主界面采用圆角设计，与现代操作系统（如MacOS、Win11）风格一致。
   - 支持无边框窗口设计，通过重写`paintEvent`实现背景自定义。
   - 使用QSS样式表和矢量图标库，提升UI美观度。

3. **用户体验优化**
   - 支持首次运行时自动生成数据库文件和配置文件。
   - 提供简洁的使用说明，帮助用户快速上手。

### **三、技术实现**
#### **3.1 技术栈**
- **开发框架**：Qt5 GUI框架
- **音频模块**：Qt Multimedia（QMediaPlayer）
- **数据库**：SQLite
- **UI设计**：QSS样式表、矢量图标库

#### **3.2 主要类设计**
1. **Music类**
   - **功能**：存储歌曲信息，支持歌词路径解析。
   - **属性**：歌曲URL、歌手名、歌曲名、专辑名、时长、比特率。
   - **方法**：获取歌曲信息、解析歌词路径、存入数据库。

2. **MusicList类**
   - **功能**：管理歌单，支持增删改查。
   - **属性**：歌单名称、歌曲列表。
   - **方法**：添加歌曲、删除歌曲、保存到数据库。

3. **MainWidget类**
   - **功能**：主窗口UI设计，支持自定义背景和圆角设计。
   - **方法**：重写`paintEvent`实现背景绘制，设置无边框窗口。

#### **3.3 数据库设计**
- **数据库文件**：`Music.db`（SQLite本地数据库）
  - 表结构：`songs`表（歌曲信息）、`playlists`表（歌单信息）、`playlist_songs`表（歌单与歌曲关联）。
- **配置文件**：`LightMusicPlayer.ini`（保存用户设置，如背景图片路径）。

### **四、文档规范**
#### **4.1 文档内容**
1. **软件使用说明**（必须）
   - 详细描述如何添加音乐、控制播放、管理歌单、显示歌词等功能。
   - 提供首次运行时生成的文件说明（数据库文件、配置文件）。

2. **软件设计说明**（必须）
   - 描述UI设计思路、功能模块设计、数据库结构。
   - 提供关键技术点的实现原理（如歌词解析、自定义背景实现）。

3. **软件设计心得体会**（可选）
   - 总结项目开发过程中的技术难点和解决方案。
   - 分享对Qt5框架和SQLite数据库的理解与应用。

#### **4.2 文档要求**
- 文档不少于1000字。
- 文档结构清晰，内容详实，语言规范。

### **五、项目计划**
#### **5.1 开发阶段**
1. **需求分析与设计**：1周
2. **核心功能开发**：2周
3. **UI设计与优化**：1周
4. **测试与调试**：1周

#### **5.2 交付物**
- 可运行的本地音乐播放器软件。
- 详细的软件文档（使用说明、设计说明、心得体会）。

### **六、风险评估**
1. **技术风险**
   - 歌词文件编码问题可能导致乱码，需提前测试不同编码格式。
   - 自定义UI设计可能增加开发复杂度，需查阅相关资料解决。

2. **时间风险**
   - 功能开发过程中可能遇到未预料的技术难题，需预留缓冲时间。

3. **资源风险**
   - 依赖第三方库（如矢量图标库）可能影响项目进度，需提前准备替代方案。

### **七、总结**
本项目通过Qt5框架开发了一个功能完善、界面美观的本地音乐播放器，提升了个人的编程能力和文档撰写能力。通过本次项目，深入理解了Qt5多媒体模块和SQLite数据库的使用，掌握了正则表达式在歌词解析中的应用，以及自定义UI的设计方法。
