import 'dotenv/config';
import { IParametrosConfiguracao } from '../../../src/types';

const config: IParametrosConfiguracao = {
  ip: '1=192.168.250.10;2=192.168.43.218',
  loja: '00000139',
  terminal: '00000051',
  reservado: process.env.SITEF_RESERVADO || '',
  parametrosAdicionais: '[79430682025540;08568632000168]',
};

export default config;
