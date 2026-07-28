# Samuel Menu

## Estrutura

```
Samuel Menu/
├── menu/           # C++ cheat (FiveM/Steam)
│   ├── hyperx.sln
│   ├── packages/   # NuGet dependencies
│   └── ...
├── bot/            # Discord bot (Node.js)
│   ├── src/
│   │   ├── index.js
│   │   ├── commands/
│   │   └── services/
│   └── package.json
├── host/           # Backend API (Node.js + PostgreSQL)
│   ├── src/
│   │   ├── index.js
│   │   ├── config/
│   │   ├── middleware/
│   │   ├── models/
│   │   └── routes/
│   ├── login-ui/   # Página de login
│   ├── admin-panel/
│   ├── .env
│   ├── railway.json
│   └── package.json
└── client-sdk/     # KeyAuth SDK exemplos (C#/C++)
```

## Como Rodar

### Host (backend)
```bash
cd host
npm install
cp .env.example .env  # edite com seus dados
npm run dev
```

### Bot (Discord)
```bash
cd bot
npm install
# .env compartilhado com host/
npm run dev
```

### Menu (C++)
Abra `menu/hyperx.sln` no Visual Studio e compile.
