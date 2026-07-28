require('dotenv').config({ path: require('path').join(__dirname, '..', '..', 'host', '.env') });
const { Client, GatewayIntentBits, REST, Routes, Collection, EmbedBuilder } = require('discord.js');
const fs = require('fs');
const path = require('path');
const api = require('./services/api');

const client = new Client({
    intents: [
        GatewayIntentBits.Guilds,
        GatewayIntentBits.GuildMessages,
        GatewayIntentBits.MessageContent
    ]
});

client.commands = new Collection();

const commandsPath = path.join(__dirname, 'commands');
const commandFiles = fs.readdirSync(commandsPath).filter(f => f.endsWith('.js'));

for (const file of commandFiles) {
    const command = require(path.join(commandsPath, file));
    if ('data' in command && 'execute' in command) {
        client.commands.set(command.data.name, command);
    }
}

client.once('ready', async () => {
    console.log(`[DISCORD] Logged in as ${client.user.tag}`);
    try {
        const commands = client.commands.map(cmd => cmd.data.toJSON());
        const rest = new REST({ version: '10' }).setToken(process.env.DISCORD_BOT_TOKEN);
        await rest.put(Routes.applicationCommands(process.env.DISCORD_CLIENT_ID), { body: commands });
        console.log(`[DISCORD] Registered ${commands.length} slash commands`);
    } catch (error) {
        console.error('[DISCORD] Failed to register commands:', error);
    }
});

client.on('interactionCreate', async interaction => {
    if (interaction.isChatInputCommand()) {
        const command = client.commands.get(interaction.commandName);
        if (!command) return;
        try {
            await command.execute(interaction);
        } catch (error) {
            console.error(`[DISCORD] Error executing ${interaction.commandName}:`, error);
            await interaction.reply({ content: 'Ocorreu um erro ao executar este comando.', ephemeral: true });
        }
        return;
    }
    if (interaction.isButton()) {
        if (interaction.customId === 'painel_gerar') {
            await interaction.reply({ content: 'Use `/gerarkey` para gerar chaves.', ephemeral: true });
        } else if (interaction.customId === 'painel_logs') {
            try {
                const logs = await api.getStats();
                const embed = new EmbedBuilder()
                    .setColor(0x3498DB)
                    .setTitle('📊 Estatísticas do Sistema')
                    .addFields(
                        { name: '🗝️ Ativas', value: `${logs.active}`, inline: true },
                        { name: '👥 Sessões', value: `${logs.activeSessions}`, inline: true },
                        { name: '🚫 Banidas', value: `${logs.banned}`, inline: true }
                    )
                    .setFooter({ text: 'Key Auth System' })
                    .setTimestamp();
                await interaction.reply({ embeds: [embed], ephemeral: true });
            } catch {
                await interaction.reply({ content: '❌ API offline.', ephemeral: true });
            }
        }
    }
});

const token = process.env.DISCORD_BOT_TOKEN;
if (!token) {
    console.error('[DISCORD] Bot token not found in .env');
    process.exit(1);
}
client.login(token);
