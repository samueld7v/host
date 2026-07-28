const { SlashCommandBuilder, EmbedBuilder } = require('discord.js');
const api = require('../services/api');

const LOG_CHANNEL_ID = process.env.DISCORD_LOG_CHANNEL || '1531480962800681070';
const ADMIN_ROLE_ID = process.env.DISCORD_ADMIN_ROLE || '1531481052051144915';

module.exports = {
    data: new SlashCommandBuilder()
        .setName('banir')
        .setDescription('Bane permanentemente uma chave ou HWID')
        .addStringOption(option =>
            option.setName('alvo')
                .setDescription('Chave ou HWID para banir')
                .setRequired(true))
        .addStringOption(option =>
            option.setName('motivo')
                .setDescription('Motivo do banimento')
                .setRequired(false)),
    async execute(interaction) {
        if (!interaction.member.roles.cache.has(ADMIN_ROLE_ID)) {
            return interaction.reply({ content: '❌ Sem permissão.', ephemeral: true });
        }
        await interaction.deferReply({ ephemeral: true });
        const target = interaction.options.getString('alvo');
        const reason = interaction.options.getString('motivo') || 'Não especificado';
        try {
            if (target.length >= 32) {
                await api.banHwid(target, reason);
                const embed = new EmbedBuilder()
                    .setColor(0xFF0000)
                    .setTitle('🚫 HWID Banido')
                    .setDescription(`HWID \`${target.substring(0, 16)}...\` banido.\nMotivo: ${reason}`);
                await interaction.editReply({ embeds: [embed] });
                await logToChannel(interaction.client, `🚫 ${interaction.user.tag} baniu HWID \`${target.substring(0, 16)}...\` — ${reason}`);
            } else {
                await api.banKey(target);
                const embed = new EmbedBuilder()
                    .setColor(0xFF0000)
                    .setTitle('🚫 Chave Banida')
                    .setDescription(`Chave \`${target}\` banida.\nMotivo: ${reason}`);
                await interaction.editReply({ embeds: [embed] });
                await logToChannel(interaction.client, `🚫 ${interaction.user.tag} baniu chave \`${target}\` — ${reason}`);
            }
        } catch {
            await interaction.editReply({ content: '❌ Erro ao banir. Alvo não encontrado.' });
        }
    }
};

async function logToChannel(client, message) {
    try {
        const channel = await client.channels.fetch(LOG_CHANNEL_ID);
        if (channel) channel.send(`[\`${new Date().toLocaleString('pt-BR')}\`] ${message}`);
    } catch {}
}
