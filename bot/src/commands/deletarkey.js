const { SlashCommandBuilder, EmbedBuilder } = require('discord.js');
const api = require('../services/api');

const LOG_CHANNEL_ID = process.env.DISCORD_LOG_CHANNEL || '1531480962800681070';
const ADMIN_ROLE_ID = process.env.DISCORD_ADMIN_ROLE || '1531481052051144915';

module.exports = {
    data: new SlashCommandBuilder()
        .setName('deletarkey')
        .setDescription('Revoga/deleta uma chave permanentemente')
        .addStringOption(option =>
            option.setName('chave')
                .setDescription('Chave para deletar')
                .setRequired(true)),
    async execute(interaction) {
        if (!interaction.member.roles.cache.has(ADMIN_ROLE_ID)) {
            return interaction.reply({ content: '❌ Sem permissão.', ephemeral: true });
        }
        await interaction.deferReply({ ephemeral: true });
        const key = interaction.options.getString('chave');
        try {
            const result = await api.deleteKey(key);
            const embed = new EmbedBuilder()
                .setColor(result.success ? 0xFF4444 : 0xFF0000)
                .setTitle(result.success ? '🗑️ Chave Deletada' : '❌ Falha')
                .setDescription(result.success
                    ? `Chave \`${key}\` foi deletada permanentemente.`
                    : `Chave \`${key}\` não encontrada.`);
            await interaction.editReply({ embeds: [embed] });
            if (result.success) await logToChannel(interaction.client, `🗑️ ${interaction.user.tag} deletou chave \`${key}\``);
        } catch {
            await interaction.editReply({ content: '❌ Erro ao deletar chave.' });
        }
    }
};

async function logToChannel(client, message) {
    try {
        const channel = await client.channels.fetch(LOG_CHANNEL_ID);
        if (channel) channel.send(`[\`${new Date().toLocaleString('pt-BR')}\`] ${message}`);
    } catch {}
}
