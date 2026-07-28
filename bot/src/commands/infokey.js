const { SlashCommandBuilder, EmbedBuilder } = require('discord.js');
const api = require('../services/api');

const LOG_CHANNEL_ID = process.env.DISCORD_LOG_CHANNEL || '1531480962800681070';
const ADMIN_ROLE_ID = process.env.DISCORD_ADMIN_ROLE || '1531481052051144915';

module.exports = {
    data: new SlashCommandBuilder()
        .setName('infokey')
        .setDescription('Exibe informações detalhadas de uma chave')
        .addStringOption(option =>
            option.setName('chave')
                .setDescription('Chave para consultar')
                .setRequired(true)),
    async execute(interaction) {
        if (!interaction.member.roles.cache.has(ADMIN_ROLE_ID)) {
            return interaction.reply({ content: '❌ Sem permissão.', ephemeral: true });
        }
        await interaction.deferReply({ ephemeral: true });
        const key = interaction.options.getString('chave');
        try {
            const info = await api.getKeyInfo(key);
            const statusEmoji = { active: '✅', expired: '⏳', banned: '🚫', unused: '📦' };
            const embed = new EmbedBuilder()
                .setColor(0x3498DB)
                .setTitle('🔍 Informações da Chave')
                .addFields(
                    { name: 'Status', value: `${statusEmoji[info.status] || '❓'} ${info.status}`, inline: true },
                    { name: 'Plano', value: info.plan_type, inline: true },
                    { name: 'Duração', value: `${info.duration} dias`, inline: true },
                    { name: 'Criada em', value: info.created_at || 'N/A', inline: true },
                    { name: 'Expira em', value: info.expires_at || 'N/A', inline: true },
                    { name: 'Último Login', value: info.last_login || 'Nunca', inline: true },
                    { name: 'HWID', value: info.hwid ? `\`${info.hwid.substring(0, 20)}...\`` : 'Não vinculado', inline: false },
                    { name: 'IP', value: info.ip_address || 'N/A', inline: true },
                    { name: 'Criado por', value: info.created_by || 'N/A', inline: true }
                )
                .setFooter({ text: `ID: ${info.id}` })
                .setTimestamp();
            await interaction.editReply({ embeds: [embed] });
        } catch {
            await interaction.editReply({ content: '❌ Chave não encontrada.' });
        }
    }
};
