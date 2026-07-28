# KeyAuth System — Sistema de Autenticação por Chaves

Sistema completo de autenticação com **Backend API**, **Bot Discord**, **Painel Web Admin** e **Client SDK** (C++/C#).

## Estrutura do Projeto

```
📦 Samuel Menu/
├── backend/               # API REST (Node.js + Express + SQLite)
│   ├── src/
│   │   ├── index.js       # Servidor principal
│   │   ├── config/        # Config DB e constantes
│   │   ├── middleware/     # Segurança, rate-limit, criptografia
│   │   ├── models/        # KeyManager (lógica de chaves)
│   │   └── routes/        # auth.js (cliente) + admin.js (painel)
│   ├── .env               # Configurações (alterar antes de usar)
│   └── package.json
├── discord-bot/            # Bot Discord (discord.js v14)
│   ├── src/
│   │   ├── index.js       # Bot principal + slash commands
│   │   ├── commands/      # /painel, /gerarkey, /infokey, etc.
│   │   └── services/      # Integração com a API
│   └── package.json
├── admin-panel/            # Painel Web (HTML + Tailwind + JS)
│   └── index.html
├── client-sdk/             # SDKs de exemplo
│   ├── csharp/            # KeyAuthClient.cs + Example.cs
│   └── cpp/               # keyauth.cpp (WinHTTP + WMI)
└── README.md
```

## Instalação

### 1. Backend

```bash
cd backend
npm install
# Edite .env com suas configurações
npm run dev
```

### 2. Discord Bot

```bash
cd discord-bot
npm install
# O .env fica em backend/.env (compartilhado)
npm run dev
```

### 3. Painel Web

O painel é servido automaticamente pelo backend em:

```
http://localhost:3000/panel
```

### 4. Client SDK

- **C#**: Abra `client-sdk/csharp/` no Visual Studio, compile e execute.
- **C++**: Requer `nlohmann/json` (vcpkg: `vcpkg install nlohmann-json`).

## Configuração (.env)

| Variável | Descrição |
|---|---|
| `API_PORT` | Porta do servidor (default: 3000) |
| `ENCRYPTION_SECRET` | Chave AES-256-GCM para payloads criptografados |
| `JWT_SECRET` | Segredo para tokens JWT |
| `API_SECRET_KEY` | Chave de API para client-sdk |
| `DISCORD_BOT_TOKEN` | Token do bot Discord |
| `DISCORD_CLIENT_ID` | ID do aplicativo Discord |
| `DISCORD_LOG_CHANNEL` | Canal de logs do bot |
| `DISCORD_ADMIN_ROLE` | Cargo com permissão para comandos |

## Comandos do Discord

| Comando | Descrição |
|---|---|
| `/painel` | Estatísticas e menu interativo |
| `/gerarkey [plano] [qtde]` | Gera chaves em lote |
| `/infokey [chave]` | Info detalhada da chave |
| `/resethwid [chave]` | Reseta HWID |
| `/deletarkey [chave]` | Deleta chave |
| `/banir [alvo] [motivo]` | Bane chave ou HWID |

## API Endpoints

### Cliente
- `POST /api/auth/handshake` — Autenticar com key + hwid
- `POST /api/auth/verify` — Verificar sessão
- `POST /api/auth/encrypted-handshake` — Handshake criptografado

### Admin (requer JWT)
- `POST /api/admin/login` — Login
- `GET /api/admin/stats` — Estatísticas
- `GET /api/admin/keys` — Listar chaves
- `POST /api/admin/keys/generate` — Gerar chaves
- `POST /api/admin/keys/reset-hwid` — Resetar HWID
- `POST /api/admin/keys/extend` — Estender tempo
- `POST /api/admin/keys/ban` / `unban` / `delete` — Gerenciar
- `GET /api/admin/logs` — Logs
- `POST /api/admin/change-password` — Alterar senha

## Segurança

- HWID composto (Motherboard + CPU + Disk + MAC) com SHA-256
- Rate limiting por IP e HWID
- Anti-debug no client C++ (IsDebuggerPresent + NtDll integrity)
- Payloads criptografados AES-256-GCM (opcional)
- Sessões JWT com expiração
- Senhas com bcrypt (salt rounds = 12)
- Bloqueio automático por excesso de tentativas
