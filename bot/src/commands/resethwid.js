const { SlashCommandBuilder, EmbedBuilder } = require('discord.js');
const api = require('../services/api');

const LOG_CHANNEL_ID = process.env.DISCORD_LOG_CHANNEL || '1531480962800681070';
const ADMIN_ROLE_ID = process.env.DISCORD_ADMIN_ROLE || '1531481052051144915';

module.exports = {
    data: new SlashCommandBuilder()
        .setName('resethwid')
        .setDescription('Reseta o HWID atrelado a uma chave')
        .addStringOption(option =>
            option.setName('chave')
                .setDescription('Chave para resetar o HWID')
                .setRequired(true)),
    async execute(interaction) {
        if (!interaction.member.roles.cache.has(ADMIN_ROLE_ID)) {
            return interaction.reply({ content: '❌ Sem permissão.', ephemeral: true });
        }
        await interaction.deferReply({ ephemeral: true });
        const key = interaction.options.getString('chave');
        try {
            const result = await api.resetHwid(key);
            const embed = new EmbedBuilder()
                .setColor(result.success ? 0xFFA500 : 0xFF0000)
                .setTitle(result.success ? '🔄 HWID Resetado' : '❌ Falha')
                .setDescription(result.success
                    ? `HWID da chave \`${key}\` foi resetado.`
                    : `Chave \`${key}\` não encontrada ou banida.`);
            await interaction.editReply({ embeds: [embed] });
            if (result.success) await logToChannel(interaction.client, `🔄 ${interaction.user.tag} resetou HWID da chave \`${key}\``);
        } catch {
            await interaction.editReply({ content: '❌ Erro ao resetar HWID.' });
        }
    }
};

async function logToChannel(client, message) {
    try {
        const channel = await client.channels.fetch(LOG_CHANNEL_ID);
        if (channel) channel.send(`[\`${new Date().toLocaleString('pt-BR')}\`] ${message}`);
    } catch {}
}
