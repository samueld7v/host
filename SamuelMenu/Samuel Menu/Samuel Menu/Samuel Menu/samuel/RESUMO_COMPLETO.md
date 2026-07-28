# SISTEMA "MUNDO SOLO" / "MUNDO TÓXICO" - VARREdura COMPLETA

## 1. A MENSAGEM (HUD)
**Arquivo:** `originals\html-css-js\index.html` (linhas 280-287)
```html
<div id="warn-world">
    <p>AVISO</p>
    <span>Você está em mundo solo. Suba suporte imediatamente para regularizar seu personagem!</span>
</div>
<div id="alert-world">
    <p>AVISO</p>
    <span>Você está em mundo solo. Suba suporte imediatamente para regularizar seu personagem!</span>
</div>
```

## 2. FLUXO COMPLETO DO SISTEMA

### A) Player é marcado como tóxico
**Arquivo:** `originals\server-lua\admin-core.lua` (linhas 3447-3461)
- Comando `/toxico [passaporte]` → marca o player como tóxico no banco
- Comando `/untoxico [passaporte]` → remove a marcação
- Comando `/mundotoxico` → admin entra no mundo tóxico (bucket 5)
- Ao conectar, se `Identity["toxic"] == 1`, o player é automaticamente setado como tóxico

### B) ChangePlayerBucket força Route = 5
**Arquivo:** `originals\server-lua\vrp-player.lua` (linhas 932-949)
```lua
function ChangePlayerBucket(Source,Bucket)
    if exports["admin"]:isPlayerToxic(Source) then
        Bucket = 5  -- FORÇA bucket 5 se for tóxico
    end
    SetPlayerRoutingBucket(Source,Bucket)
    Player(Source)["state"]["Route"] = Bucket  -- Sincroniza state bag
end
```

### C) HUD detecta Route == 5 e mostra o aviso
**Arquivo:** `originals\server-lua\core.lua` (linha 110-114) - client-side
```lua
if LocalPlayer["state"]["Route"] == 5 then
    SendNUIMessage({ Action = "WorldWarn", WorldWarn = true })
else
    SendNUIMessage({ Action = "WorldWarn", WorldWarn = false })
end
```

### D) JavaScript exibe/esconde o aviso
**Arquivo:** `originals\html-css-js\main.js` (linhas 245-261)
```js
WorldWarn: function (data) {
    if (data.WorldWarn) {
        $("#warn-world").css("display", "block")
    } else {
        $("#warn-world").css("display", "none")
    }
},
AlertWarn: function (data) {
    if (data.AlertWarn) {
        $("#alert-world").html(`<p>${data.title}</p>`)
        $("#alert-world").html(`<p>${data.text}</p>`)
        $("#alert-world").css("display", "block")
    } else {
        $("#alert-world").html("")
        $("#alert-world").css("display", "none")
    }
},
```

### E) CSS do aviso
**Arquivo:** `originals\html-css-js\main.css` (linhas 1148-1228)
- `#warn-world` e `#alert-world` ficam ocultos por padrão (`display: none`)
- Usam fonte Rajdhani, cor principal, animação pulse
- Título em 5vw, texto em 1.8vw

## 3. NOTIFICAÇÕES (Mundo Tóxico)
**Arquivo:** `originals\server-lua\shared.lua`
- `#mundotoxico` = "MUNDO TOXICO" / "Você entrou no mundo tóxico."
- `#toxico` = "PASSAPORTE TOXICO" / "Você setou o passaporte X como tóxico."
- `#untoxico` = "SETADO NORMAL" / "Você setou o passaporte X como normal."
- `#mundopadrao` = "MUNDO PADRAO" / "Você entrou no mundo padrão."

## 4. WEBHOOK DISCORD
**Arquivo:** `originals\server-lua\Discords.lua` (linha 22)
- `untoxico` webhook: enviado quando admin tira alguém do mundo tóxico

## 5. COMANDOS DO SISTEMA
| Comando | Descrição |
|---------|-----------|
| `/toxico [passaporte]` | Marca player como tóxico (admin/aliado) |
| `/untoxico [passaporte]` | Remove marcação tóxico (admin) |
| `/mundotoxico` | Admin entra no mundo tóxico (bucket 5) |
| `/mundopadrao` | Admin volta ao mundo padrão (bucket 1) |

## 6. ARQUIVOS ORIGINAIS SALVOS

### `originals\html-css-js\`
- `index.html` - HUD completo com os elementos warn-world e alert-world
- `main.js` - JavaScript do HUD (funções WorldWarn e AlertWarn)
- `main.css` - Estilos CSS completos
- `fxmanifest.lua` - Manifest do resource hud

### `originals\server-lua\`
- `core.lua` - Client-side do hud (linha 110: trigger do Route == 5)
- `core.lua` (server-side) - Server-side do hud
- `admin-core.lua` - Admin core (Toxics table, isPlayerToxic, comandos toxico/untoxico/mundotoxico)
- `vrp-player.lua` - VRP player (ChangePlayerBucket que força bucket 5)
- `vrp-base.lua` - VRP base (SaveTemporary, vRP:BucketServer)
- `vrp-gui.lua` - VRP gui (inicializa Route = 0)
- `shared.lua` - Notificações do sistema (#mundotoxico, #toxico, #untoxico)
- `Discords.lua` - Webhooks (untoxico)

## 7. RESUMO DO FLUXO
```
Player é marcado tóxico → 
  admin-core.lua: TriggerEvent("vRP:SetToxic", passport, true) →
    vrp-player.lua: ChangePlayerBucket(source, 5) →
      Player(state)["Route"] = 5 →
        hud core.lua: LocalPlayer["state"]["Route"] == 5 →
          SendNUIMessage(WorldWarn = true) →
            main.js: $("#warn-world").show() →
              "Você está em mundo solo. Suba suporte imediatamente..."
```
