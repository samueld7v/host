const { SlashCommandBuilder, EmbedBuilder } = require('discord.js');
const api = require('../services/api');

const LOG_CHANNEL_ID = process.env.DISCORD_LOG_CHANNEL || '1531480962800681070';
const ADMIN_ROLE_ID = process.env.DISCORD_ADMIN_ROLE || '1531481052051144915';

const PLANOS = {
    'trial': { label: 'Trial', duration: 1 },
    'mensal': { label: 'Mensal', duration: 30 },
    'trimestral': { label: 'Trimestral', duration: 90 },
    'vitalicio': { label: 'Vitalício', duration: 36500 }
};

module.exports = {
    data: new SlashCommandBuilder()
        .setName('gerarkey')
        .setDescription('Gera uma ou mais chaves de autenticação')
        .addStringOption(option =>
            option.setName('plano')
                .setDescription('Plano da chave')
                .setRequired(true)
                .addChoices(
                    { name: 'Trial (1 dia)', value: 'trial' },
                    { name: 'Mensal (30 dias)', value: 'mensal' },
                    { name: 'Trimestral (90 dias)', value: 'trimestral' },
                    { name: 'Vitalício', value: 'vitalicio' }
                ))
        .addIntegerOption(option =>
            option.setName('quantidade')
                .setDescription('Quantidade de chaves (1-20)')
                .setRequired(false)
                .setMinValue(1)
                .setMaxValue(20))
        .addStringOption(option =>
            option.setName('prefixo')
                .setDescription('Prefixo personalizado para as chaves')
                .setRequired(false)),
    async execute(interaction) {
        if (!interaction.member.roles.cache.has(ADMIN_ROLE_ID)) {
            return interaction.reply({ content: '❌ Sem permissão.', ephemeral: true });
        }
        await interaction.deferReply({ ephemeral: true });
        const planOption = interaction.options.getString('plano');
        const plan = PLANOS[planOption];
        const count = interaction.options.getInteger('quantidade') || 1;
        const prefix = interaction.options.getString('prefixo') || '';

        try {
            const result = await api.generateKeys(plan.duration, planOption, count, prefix);
            const embed = new EmbedBuilder()
                .setColor(0x00FF88)
                .setTitle('🔑 Chaves Geradas')
                .setDescription(`**${result.count}** chave(s) criada(s) com sucesso!`)
                .addFields(
                    { name: 'Plano', value: plan.label, inline: true },
                    { name: 'Duração', value: `${plan.duration} dias`, inline: true }
                );
            if (result.keys.length <= 5) {
                const keyList = result.keys.map((k, i) => `**${i + 1}.** \`${k}\``).join('\n');
                embed.addFields({ name: 'Chaves', value: keyList });
            } else {
                embed.addFields({ name: 'Chaves', value: `${result.keys.length} chaves geradas (console)` });
            }
            await interaction.editReply({ embeds: [embed] });
            await logToChannel(interaction.client, `🔑 ${interaction.user.tag} gerou ${count} chave(s) ${plan.label}`);
        } catch (error) {
            await interaction.editReply({ content: '❌ Erro ao gerar chaves.' });
        }
    }
};

async function logToChannel(client, message) {
    try {
        const channel = await client.channels.fetch(LOG_CHANNEL_ID);
        if (channel) channel.send(`[\`${new Date().toLocaleString('pt-BR')}\`] ${message}`);
    } catch {}
}
