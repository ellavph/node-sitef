#include <napi.h>
#include "../nodesitef.hpp"

using std::string;

class LePinblockDiretoPromise : public PromiseWorker<int>
{
public:
  static Napi::Value Create(const Napi::CallbackInfo &info)
  {

    if (info.Length() < 2)
      return Reject(info.Env(), "MissingArgument");
    else if (!info[0].IsNumber() ||
             !info[1].IsString() ||
             !info[2].IsString() ||
             !info[3].IsNumber() ||
             !info[4].IsString() ||
            //  !info[5].IsFunction() ||
            //  !info[6].IsString() ||
             !info[5].IsNumber() ||
             !info[6].IsString())
      return Reject(info.Env(), "InvalidArgument");

    int iModoCripto = info[0].As<Napi::Number>().Int32Value();
    string lpcCartao = info[1].As<Napi::String>().Utf8Value();
    string lpcTuiccs = info[2].As<Napi::String>().Utf8Value();
    int iTimeout = info[3].As<Napi::Number>().Int32Value();
    string lpcParamAdic = info[4].As<Napi::String>().Utf8Value();
    int iTamMsg = info[5].As<Napi::Number>().Int32Value();
    string lpcMsg = info[6].As<Napi::String>().Utf8Value();


        // Imprimindo os valores no console (stdout)
    printf("iModoCripto: %d\n", iModoCripto);
    printf("lpcCartao: %s\n", lpcCartao.c_str());
    printf("lpcTuiccs: %s\n", lpcTuiccs.c_str());
    printf("iTimeout: %d\n", iTimeout);
    printf("lpcParamAdic: %s\n", lpcParamAdic.c_str());
    printf("iTamMsg: %d\n", iTamMsg);
    printf("lpcMsg: %s\n", lpcMsg.c_str());


    LePinblockDiretoPromise *worker = new LePinblockDiretoPromise(info.Env(),
                                                                  iModoCripto,
                                                                  lpcCartao,
                                                                  lpcTuiccs,
                                                                  iTimeout,
                                                                  lpcParamAdic,
                                                                  iTamMsg,
                                                                  lpcMsg);
    worker->Queue();
    return worker->deferredPromise.Promise();
  }

protected:
  void Execute() override
  {
    result = lePinblockDireto(iModoCripto,
                              lpcCartao.c_str(),
                              lpcTuiccs.c_str(),
                              iTimeout,
                              lpcParamAdic.c_str(),
                              iTamMsg,
                              lpcMsg.c_str());
  }

  virtual void OnOK() override
  {
    // Resolve a Promise com o resultado obtido
    Napi::Object obj = Napi::Object::New(Env());
    obj.Set("retorno", result);
    obj.Set("iTamMsg", iTamMsg);

    deferredPromise.Resolve(obj);
  }

private:
  LePinblockDiretoPromise(napi_env env,
                          int p_iModoCripto,
                          std::string p_lpcCartao,
                          std::string p_lpcTuiccs,
                          int p_iTimeout,
                          std::string p_lpcParamAdic,
                          // Napi::Function p_pTstCancela,
                          // std::string p_lpcSaida,
                          int p_iTamMsg,
                          std::string p_lpcMsg)
    : PromiseWorker(env),
      iModoCripto(p_iModoCripto),
      lpcCartao(p_lpcCartao),
      lpcTuiccs(p_lpcTuiccs),
      iTimeout(p_iTimeout),
      lpcParamAdic(p_lpcParamAdic),
      // pTstCancela(p_pTstCancela),
      // lpcSaida(p_lpcSaida),
      iTamMsg(p_iTamMsg),
      lpcMsg(p_lpcMsg)
  {
  }

  int iModoCripto;
  std::string lpcCartao;
  std::string lpcTuiccs;
  int iTimeout;
  std::string lpcParamAdic;
  // Napi::Function pTstCancela; // Função de callback
  // std::string lpcSaida;
  int iTamMsg;
  std::string lpcMsg;
  int result;
};
