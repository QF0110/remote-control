# Git 多账号使用说明

> 仓库：`C:\Users\17232\Desktop\传递\user`（`.git` 在这个目录）
> 远程：`QF0110/remote-control`
> 本机两个 GitHub 账号：**QF0110**、**make82378-bit**

---

## 一、本机已有的东西（一次性配好，不用再改）

### 两把密钥

| 账号 | 私钥 | 公钥 |
|---|---|---|
| QF0110 | `C:\Users\17232\.ssh\id_QF0110` | `id_QF0110.pub` |
| make82378-bit | `C:\Users\17232\.ssh\id_make82378-bit` | `id_make82378-bit.pub` |

公钥分别已加到对应 GitHub 账号的 `Settings → SSH and GPG keys`。

### `~/.ssh/config` 里的两个别名

```
Host github-qf
  HostName github.com
  User git
  IdentityFile C:/Users/17232/.ssh/id_QF0110
  IdentitiesOnly yes

Host github-make
  HostName github.com
  User git
  IdentityFile C:/Users/17232/.ssh/id_make82378-bit
  IdentitiesOnly yes
```

**别名就是连接方式的名字**，`git@github-qf:...` 和 `git@github-make:...` 指向同一个 GitHub，区别只是用哪把 key。

---

## 二、两个 remote（一次性配好）

```powershell
cd "C:\Users\17232\Desktop\传递\user"
git remote add qf   git@github-qf:QF0110/remote-control.git
git remote add make git@github-make:QF0110/remote-control.git
```

配好后 `git remote -v` 会显示四条（每个 remote 有 fetch 和 push 两行）。

> 如果之前已经有 `origin`，可以留着，也可以 `git remote remove origin`。下面都用 `qf` / `make` 这两个名字。

---

## 三、日常操作（最常用）

### 用 QF0110 提交并推送

```powershell
cd "C:\Users\17232\Desktop\传递\user"

git config user.name "QF0110"
git config user.email "QF0110@users.noreply.github.com"

git add .
git commit -m "改了什么"
git push qf main
```

### 用 make82378-bit 提交并推送

```powershell
cd "C:\Users\17232\Desktop\传递\user"

git config user.name "make82378-bit"
git config user.email "make82378-bit@users.noreply.github.com"

git add .
git commit -m "改了什么"
git push make main
```

**两段都要改**：

- `git config user.name/email` → 决定 commit 里署谁的名
- `git push qf` / `git push make` → 决定用哪把 key 认证

只改一个会导致「署名和推送账号不一致」。

> `git config` 不加 `--global` 只对本仓库生效，不影响其他项目。

---

## 四、切换后的验证

```powershell
git remote -v                    # 看 remote 地址
git config user.name             # 看当前署名
git config user.email
git log -1 --format="%an <%ae>"  # 看最后一次提交的作者
```

推送前可以先单独测认证（不推代码，只握手）：

```powershell
ssh -T git@github-qf      # 应显示 Hi QF0110!
ssh -T git@github-make    # 应显示 Hi make82378-bit!
```

---

## 五、常见报错对照

| 报错 | 原因 | 处理 |
|---|---|---|
| `Permission denied (publickey)` | 用的 key 没加到对应账号 | `ssh -vT git@别名` 看它用了哪把 key，再核对 GitHub 上的公钥 |
| `Could not resolve hostname github-qf` | config 没被读到 | 检查 `C:\Users\17232\.ssh\config` 是否叫这个名字（不是 config.txt）、有没有 BOM |
| `Repository not found` | make82378-bit 没被加为协作者 | QF0110 → 仓库 Settings → Collaborators 加人，然后对方接受邀请 |
| `Key is already in use` | 同一把公钥要绑第二个账号 | 一把 key 只能绑一个 GitHub 账号，给每个账号单独生成 |
| `Connection timed out` | 22 端口被墙 | config 里把 `HostName github.com` 改成 `ssh.github.com`，加 `Port 443` |

---

## 六、一次性排错命令

```powershell
# 看 .ssh 目录里到底有什么
Get-ChildItem $env:USERPROFILE\.ssh | Select-Object Name, Length

# 看 config 内容
Get-Content $env:USERPROFILE\.ssh\config

# 看某个别名实际解析成什么
ssh -G github-qf | Select-String "hostname|identityfile"

# 看公钥指纹（和 GitHub 页面对比）
ssh-keygen -lf $env:USERPROFILE\.ssh\id_QF0110.pub
ssh-keygen -lf $env:USERPROFILE\.ssh\id_make82378-bit.pub
```

---

## 七、日常速查

| 我要做什么 | 命令 |
|---|---|
| 看改了什么 | `git status` |
| 看提交历史 | `git log --oneline` |
| 提交 | `git add .` → `git commit -m "说明"` |
| 用 QF0110 推 | `git push qf main` |
| 用 make82378-bit 推 | `git push make main` |
| 拉取别人的改动 | `git pull qf main` |
| 撤销未提交的改动 | `git checkout -- .` |
| 看某个文件的改动 | `git diff 文件名` |

---

## 八、代理说明

本机之前配过 HTTPS 代理（Clash 7890），SSH 用不到它，可以清掉：

```powershell
git config --global --unset http.proxy
git config --global --unset https.proxy
```

如果以后 SSH 也连不上，把 `~/.ssh/config` 里两个块的 `HostName` 改成 `ssh.github.com`，并各加一行 `Port 443`。
