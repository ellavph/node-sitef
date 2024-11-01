import chalk from 'chalk';

export default (error: Error) => {
  const message = error.message || `Erro desconhecido (${error.name}).`;
  console.log(message, '\n');
};
