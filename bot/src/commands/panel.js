const { SlashCommandBuilder, EmbedBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle } = require('discord.js');
const api = require('../services/api');

const LOG_CHANNEL_ID = process.env.DISCORD_LOG_CHANNEL || '1531480962800681070';
const ADMIN_ROLE_ID = process.env.DISCORD_ADMIN_ROLE || '1531481052051144915';

module.exports = {
    data: new SlashCommandBuilder()
        .setName('painel')
        .setDescription('Exibe o painel de controle com estatísticas e atalhos'),
    async execute(interaction) {
        if (!interaction.member.roles.cache.has(ADMIN_ROLE_ID)) {
            return interaction.reply({ content: '❌ Você não tem permissão para usar este comando.', ephemeral: true });
        }
        await interaction.deferReply({ ephemeral: true });
        try {
            const stats = await api.getStats();
            const embed = new EmbedBuilder()
                .setColor(0x00FF88)
                .setTitle('SISTEMA DE AUTENTICAÇÃO — PAINEL')
                .setDescription('Resumo do sistema de chaves')
                .addFields(
                    { name: '🗝️ Ativas', value: `${stats.active}`, inline: true },
                    { name: '⏳ Expiradas', value: `${stats.expired}`, inline: true },
                    { name: '🚫 Banidas', value: `${stats.banned}`, inline: true },
                    { name: '📦 Não Usadas', value: `${stats.unused}`, inline: true },
                    { name: '📊 Total', value: `${stats.total}`, inline: true },
                    { name: '👥 Sessões Ativas', value: `${stats.activeSessions}`, inline: true }
                )
                .setFooter({ text: 'Key Auth System v2.0' })
                .setTimestamp();
            const row = new ActionRowBuilder()
                .addComponents(
                    new ButtonBuilder()
                        .setCustomId('painel_gerar')
                        .setLabel('Gerar Key')
                        .setStyle(ButtonStyle.Primary)
                        .setEmoji('🔑'),
                    new ButtonBuilder()
                        .setCustomId('painel_logs')
                        .setLabel('Últimos Logs')
                        .setStyle(ButtonStyle.Secondary)
                        .setEmoji('📜'),
                    new ButtonBuilder()
                        .setLabel('Abrir Painel Web')
                        .setStyle(ButtonStyle.Link)
                        .setURL(process.env.PANEL_URL || 'http://localhost:3000/panel')
                );
            await interaction.editReply({ embeds: [embed], components: [row] });
            await logToChannel(interaction.client, `📊 ${interaction.user.tag} visualizou o painel`);
        } catch (error) {
            await interaction.editReply({ content: '❌ Erro ao carregar painel. API offline?' });
        }
    }
};

async function logToChannel(client, message) {
    try {
        const channel = await client.channels.fetch(LOG_CHANNEL_ID);
        if (channel) channel.send(`[\`${new Date().toLocaleString('pt-BR')}\`] ${message}`);
    } catch {}
}
