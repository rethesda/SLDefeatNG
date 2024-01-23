#pragma once

#include <DefeatSpinLock.h>
#include <DefeatUtils.h>
#include <DefeatPapyrus.h>
#include <DefeatForms.h>


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace SexLabDefeat {
    
    namespace PapyrusInterface {
        using StringSetVar = ObjectVariable<std::set<std::string_view>>;
        using StringSetVarPtr = std::unique_ptr<StringSetVar>;

        using StringVar = ObjectVariable<std::string_view>;
        using StringVarPtr = std::unique_ptr<StringVar>;

        using BoolVar = ObjectVariable<bool>;
        using BoolVarPtr = std::unique_ptr<BoolVar>;

        using FloatVar = ObjectVariable<float>;
        using FloatVarPtr = std::unique_ptr<FloatVar>;
    }

    class IDefeatManager;

    class DefeatConfig {
    public:
        DefeatConfig() = default;
        ~DefeatConfig() = default;

        struct Configuration {
            PapyrusInterface::FloatVarPtr PvicRaped;
            PapyrusInterface::FloatVarPtr NVNRapedFollower;
            PapyrusInterface::FloatVarPtr NVNRaped;
            PapyrusInterface::BoolVarPtr EveryonePvic;
            PapyrusInterface::BoolVarPtr HuntCrea;

            PapyrusInterface::BoolVarPtr SexualityPvic;
            PapyrusInterface::BoolVarPtr SexualityNVN;
            PapyrusInterface::BoolVarPtr MaleHunterPvic;
            PapyrusInterface::BoolVarPtr FemaleHunterPvic;
            PapyrusInterface::BoolVarPtr HuntFCrea;
            PapyrusInterface::BoolVarPtr MaleOnGal;
            PapyrusInterface::BoolVarPtr GalOnGal;
            PapyrusInterface::BoolVarPtr MaleOnMale;
            PapyrusInterface::BoolVarPtr GalOnMale;
            PapyrusInterface::BoolVarPtr CreaOnFemale;
            PapyrusInterface::BoolVarPtr CreaFemaleOnFemale;
            PapyrusInterface::BoolVarPtr CreaFemaleOnMale;
            PapyrusInterface::BoolVarPtr CreaOnMale;
            PapyrusInterface::BoolVarPtr BeastImmunity;


            PapyrusInterface::BoolVarPtr KDWayThreshold;
            PapyrusInterface::BoolVarPtr KDHealthBlock;
            PapyrusInterface::FloatVarPtr ChanceOnHitPvic;
            PapyrusInterface::FloatVarPtr ThresholdPvic;
            PapyrusInterface::FloatVarPtr ThresholdPvicMin;
            PapyrusInterface::FloatVarPtr KnockOutHPvic;
            PapyrusInterface::FloatVarPtr SStruggleHealthPvic;

            PapyrusInterface::BoolVarPtr KDWayStamina;
            PapyrusInterface::BoolVarPtr KDStaminaBlock;
            PapyrusInterface::BoolVarPtr KDWayStaminaOB;
            PapyrusInterface::FloatVarPtr ChanceOnHitPvicS;
            PapyrusInterface::FloatVarPtr ExhaustionPvic;
            PapyrusInterface::FloatVarPtr KnockOutSPvic;
            PapyrusInterface::FloatVarPtr SStruggleExhaustionPvic;


            PapyrusInterface::BoolVarPtr KDWayPowerAtk;
            PapyrusInterface::FloatVarPtr KDWayPowerAtkCOH;
            PapyrusInterface::FloatVarPtr PowerAtkStagger;
            PapyrusInterface::FloatVarPtr KnockOutPPvic;
            PapyrusInterface::FloatVarPtr SStrugglePowerPvic;

            PapyrusInterface::BoolVarPtr bResistQTE;

            struct {
                PapyrusInterface::BoolVarPtr DeviousFrameworkON;
                PapyrusInterface::BoolVarPtr KDWayVulnerabilityUseDFW;

                PapyrusInterface::BoolVarPtr KDWayVulnerability;
                PapyrusInterface::BoolVarPtr KDVulnerabilityBlock;
                PapyrusInterface::BoolVarPtr KDWayVulnerabilityOB;
                PapyrusInterface::FloatVarPtr ChanceOnHitPvicVulnerability;
                PapyrusInterface::FloatVarPtr VulnerabilityPvic;
                PapyrusInterface::FloatVarPtr KnockOutVulnerabilityPvic;
                PapyrusInterface::FloatVarPtr SStruggleVulnerabilityPvic;

                PapyrusInterface::BoolVarPtr KDWayDynamic;
                PapyrusInterface::FloatVarPtr KnockOutDynamicPvic;
                PapyrusInterface::FloatVarPtr SStruggleDynamicPvic;
                PapyrusInterface::FloatVarPtr DynamicDefeatOnHitBase;
                PapyrusInterface::FloatVarPtr DynamicDefeatOnHitOneHand;
                PapyrusInterface::FloatVarPtr DynamicDefeatOnHitTwoHand;
                PapyrusInterface::FloatVarPtr DynamicDefeatOnHitBow;
                PapyrusInterface::FloatVarPtr DynamicDefeatOnHitSpell;
                PapyrusInterface::FloatVarPtr DynamicDefeatVulnerabilityMult;
                PapyrusInterface::FloatVarPtr DynamicDefeatPowerAttackMult;
                PapyrusInterface::FloatVarPtr DynamicDefeatLowStaminaMult;
                PapyrusInterface::FloatVarPtr DynamicDefeatLowStaminaThreshold;
                PapyrusInterface::FloatVarPtr DynamicDefeatLowHealthMult;
                PapyrusInterface::FloatVarPtr DynamicDefeatLowHealthThreshold;
                PapyrusInterface::FloatVarPtr DynamicDefeatBackHitMult;
                PapyrusInterface::FloatVarPtr DynamicDefeatBlockReduction;
                PapyrusInterface::FloatVarPtr DynamicDefeatDepleteOverTime;

            } LRGPatch;

            PapyrusInterface::StringSetVarPtr RaceAllowedPvic;
            PapyrusInterface::StringSetVarPtr RaceAllowedNVN;

            struct {
                PapyrusInterface::BoolVarPtr UseCreatureGender;
            } SexLab;
        } Config;

        void readIniConfig();
        void Setup(SexLabDefeat::IDefeatManager* defeatManager);
        void Reset();
        void LoadScriptObjects();

        PapyrusInterface::ObjectPtr getDefeatMCMScript();
        PapyrusInterface::ObjectPtr getDefeatConfigScript();
        PapyrusInterface::ObjectPtr getSslSystemConfigScript();

        bool CFG_PAPYUNHOOK = true;
        int CFG_LOGGING = 2;
        int HIT_SPAM_GUARD_EXPIRATION_MS = 500;
        float KD_FAR_MAX_DISTANCE = 1500.0;
    private:
        boost::property_tree::ptree _iniConfig;
        std::map<std::string, std::variant<std::string, int, float, bool>> _config;

        SexLabDefeat::IDefeatManager* _defeatManager;

        PapyrusInterface::ObjectPtr DefeatMCMScr;
        PapyrusInterface::ObjectPtr defeatconfig;
        PapyrusInterface::ObjectPtr sslSystemConfig;
    };

    class DefeatWidget : public SpinLock {
    public:
        enum State { QTE_METER, DYNAMIC_WIDGET, NONE };

        PapyrusInterface::StringVarPtr widgetRoot;
        PapyrusInterface::BoolVarPtr widgetReady;

        DefeatWidget();
        ~DefeatWidget();

        bool isInitialized = false;

        [[nodiscard]] bool setVisible(bool inUITask = false);
        [[nodiscard]] bool setInvisible(bool inUITask = false);
        bool getLastVisible();
        [[nodiscard]] bool setPercent(float value, bool inUITask = false);
        float getLastPercent();

        State getState();
        [[nodiscard]] bool startDynamicWidget(bool inUITask = false);
        [[nodiscard]] bool stopDynamicWidget(bool inUITask = false);

    protected:
        bool initialize();

        std::string_view getWidgetRootId();
        std::string_view _rootId;

        RE::GPtr<RE::GFxMovieView> _hudmenu = nullptr;
        RE::UI* _ui;

        float lastPercent = 0.0;
        bool lastVisible = false;
        State state = State::NONE;
    };

    class ActorExtraData {
    public:
        bool ignoreActorOnHit = true;
        int sexLabGender = 0;
        int sexLabSexuality = 0;
        bool sexLabAllowed = 0;
        std::string sexLabRaceKey = "";
        float DFWVulnerability = 0;
        //bool defeatAllowed2PC = true;
        //bool defeatAllowed2NvN = true;
    };

    class DeferredExpiringValueCallback {
    public:
        DeferredExpiringValueCallback(std::function<void()> callback) { _callback = callback; };

        void execute() {
            _callback();
        
        };

    protected:
        std::function<void()> _callback;
    };

    template <class T>
    class DeferredExpiringValue : public SpinLock {
    public:
        DeferredExpiringValue(std::unique_ptr<DeferredExpiringValueInitializer> initializer, int expirationMs = 0,
                              int accessProlongationExpireMs = 0);
        ~DeferredExpiringValue();

        void getCallback(std::function<void()> callback);
        bool isActualValue();
        T getValue() { return _value; };
        void initializeValue(T val);

    protected:
        void accessTouch();
        void processCallbackStack();

        T _value = {};
        std::queue<std::shared_ptr<DeferredExpiringValueCallback>> _callbackQueue;
        std::unique_ptr<DeferredExpiringValueInitializer> _initializer;

        std::chrono::milliseconds _expiration;
        std::chrono::milliseconds _accessProlongationExpireMs;
        std::chrono::high_resolution_clock::time_point _expirationTime;
        std::chrono::high_resolution_clock::time_point _minTime;

    };

    class DefeatActor;
    class IDefeatActorManager;

    using DefeatActorType = std::shared_ptr<DefeatActor>;
    using HitSource = RE::FormID;
    using HitProjectile = RE::FormID;

    class IDefeatActor : public SpinLock {
    public:
        enum States { NONE, ACTIVE, DISACTIVE, KNONKOUT, STANDING_STRUGGLE, KNONKDOWN };
        enum class StateFlags : uint8_t {
            NONE = 0,
            KNOCK_ALLOWED = 1 << 0,
            // flag2 = 1 << 1,
            // flag3 = 1 << 2,
            // flag3 = 1 << 3,
            // flag3 = 1 << 4,
            // flag3 = 1 << 5,
            // flag3 = 1 << 6,
            // flag3 = 1 << 7
        };
        struct DataType {
            RE::FormID TESFormId = 0;
            clock::time_point hitImmunityExpiration = SexLabDefeat::emptyTime;
            RE::FormID lastHitAggressor = 0;
            bool isSurrender = false;
            States state = States::ACTIVE;
            StateFlags flags = StateFlags::NONE;
            float dynamicDefeat = 0;
            float vulnerability = 0;

            /* External Papyrus Data */
            clock::time_point extraDataExpiration = SexLabDefeat::emptyTime;
            float DFWVulnerability = 0;
            bool ignoreActorOnHit = true;
            int sexLabGender = -1;
            int sexLabSexuality = -1;
            bool sexLabAllowed = false;
            std::string sexLabRaceKey = "";
        };

        RE::FormID getTESFormId() const { return _data.TESFormId; }

        bool isSame(RE::Actor* actor) const {
            assert(actor != nullptr);
            return actor->GetFormID() == getTESFormId();
        };

        bool isSame(IDefeatActor* actor) const { return actor->getTESFormId() == getTESFormId(); };

        virtual bool isPlayer() { return false; };
        bool isSurrender() { return _data.isSurrender; }

        bool hasHitImmunity() const { return clock::now() < _data.hitImmunityExpiration; }
        virtual void setHitImmunityFor(std::chrono::milliseconds ms) = 0;

        RE::FormID getLastHitAggressorFormId() { return _data.lastHitAggressor; }
        virtual void setLastHitAggressor(DefeatActorType lastHitAggressor) = 0;

        States getState() { return _data.state; };
        virtual void setState(States state) = 0;

        float getDynamicDefeat() { return _data.dynamicDefeat; }
        virtual void incrementDynamicDefeat(float val) = 0;
        virtual void decrementDynamicDefeat(float val) = 0;
        virtual void resetDynamicDefeat() = 0;

        virtual float getVulnerability() { return _data.vulnerability; }
        virtual void setVulnerability(float vulnerability) = 0;

        bool isExternalPapyrusDataExpired() const { return clock::now() > _data.extraDataExpiration; }
        virtual void setExternalPapyrusDataExpirationFor(std::chrono::milliseconds ms) = 0;

        float getDFWVulnerability() { return _data.DFWVulnerability; }
        virtual void setDFWVulnerability(float vulnerability) = 0;

        bool isIgnoreActorOnHit() { return _data.ignoreActorOnHit; };
        virtual void setIgnoreActorOnHit(bool val) = 0;

        int getSexLabGender() { return _data.sexLabGender; };
        virtual void setSexLabGender(int val) = 0;

        int getSexLabSexuality() { return _data.sexLabSexuality; };
        virtual void setSexLabSexuality(int val) = 0;

        virtual bool isSexLabAllowed() { return _data.sexLabAllowed; }
        virtual void setSexLabAllowed(bool val) = 0;

        std::string getSexLabRaceKey() { return _data.sexLabRaceKey; }
        virtual void setSexLabRaceKey(std::string val) = 0;

        bool isFemale() { return getSexLabGender() == 1; }
        bool IsStraight() { return getSexLabSexuality() >= 65; }
        bool IsGay() { return getSexLabSexuality() <= 35; }
        bool IsBisexual() {
            auto ratio = getSexLabSexuality();
            return (ratio < 65 && ratio > 35);
        }

    protected:
        DataType _data;

    };

    class DefeatActor : public SpinLock {
    public:
        enum States { NONE, ACTIVE, DISACTIVE };

        DefeatActor(RE::Actor* actor, IDefeatManager* defeatManager);
        ~DefeatActor();

        RE::FormID getActorFormId() const { return _actorFormId; };
        RE::Actor* getActor();
        void setActor(RE::Actor* actor);
        IDefeatActorManager* getActorManager();

        bool isSame(RE::Actor* actor) const;
        virtual bool isPlayer() { return false; };

        bool hasHitImmunity();
        void addHitImmunity(int ms);
        void setLastHitAggressor(DefeatActorType lastHitAggressor);
        bool isSurrender();
        bool isCreature();
        bool isFollower();
        bool isSatisfied();
        bool isKDImmune();
        bool isKDAllowed();
        bool isTied();
        float getDynamicDefeat();
        SpinLock* getDynamicDefeatSpinLock();
        void resetDynamicDefeat();
        void incrementDynamicDefeat(float val);
        void decrementDynamicDefeat(float val);
        States getState();
        void setState(States state);

        virtual float getVulnerability();
        void setVulnerability(float vulnerability);

        /* DeferredExpiringValue */
        bool isIgnoreActorOnHit();

        int getSexLabGender();
        int getSexLabSexuality();
        bool isSexLabAllowed();
        std::string getSexLabRaceKey();

        bool isDefeatAllowed2PC();
        bool isDefeatAllowed2NvN();
        /* / DeferredExpiringValue */

        bool isFemale();
        bool IsStraight();
        bool IsGay();
        bool IsBisexual();

        std::atomic<bool> isSheduledDeplateDynamicDefeat = false;

        DeferredExpiringValue<ActorExtraData>* extraData;

    protected:
        RE::FormID _actorFormId;
        RE::Actor* _actor;

        float _vulnerability = 0;

        DefeatActorType _lastHitAggressor;
        bool _isSurrender = false;
        States _state = States::ACTIVE;

        std::chrono::high_resolution_clock::time_point hitImmunityExpiration;
        std::chrono::high_resolution_clock::time_point _minTime;
        IDefeatManager* _defeatManager;
        float _dynamicDefeat = 0;
        SpinLock* _dynamicDefeatSpinLock = nullptr;
    };

    class DefetPlayerActor : public DefeatActor {
    public:
        DefetPlayerActor(RE::Actor* actor, IDefeatManager* defeatManager);
        bool isPlayer() override { return true; };
        float getVulnerability() override;

        PapyrusInterface::ObjectPtr getLRGDefeatPlayerVulnerabilityScript() const;

    protected:
        PapyrusInterface::FloatVarPtr _LRGVulnerabilityVar = nullptr;
    };

    class IDefeatActorManager : public SpinLock {
    public:

        virtual DefeatActorType getPlayer() = 0;

        virtual DefeatActorType getActor(RE::Actor* actor) = 0;

        /* Pre Checks functions */
        virtual bool validForAggressorRole(RE::Actor* actor);
        virtual bool validForAggressorRoleOverPlayer(RE::Actor* actor);
        virtual bool validPlayerForVictimRole(RE::Actor* actor) = 0;
        /* / Pre Checks functions  */

        
        bool isDefeatAllowedByAgressor(DefeatActorType target, DefeatActorType aggressor);
        bool IsSexualAssaulAllowedByAggressor(DefeatActorType target, DefeatActorType aggressor);
        virtual bool hasSexInterestByAggressor(DefeatActorType target, DefeatActorType aggressor) = 0;
        virtual bool hasSexCombinationWithAggressor(DefeatActorType target, DefeatActorType aggressor) = 0;
        virtual bool checkAggressor(DefeatActorType target, DefeatActorType aggressor) = 0;

        float getDistanceBetween(DefeatActorType source, DefeatActorType target);
        float getHeadingAngleBetween(DefeatActorType source, DefeatActorType target);
        float getActorValuePercentage(DefeatActorType source, RE::ActorValue av);
        RE::TESForm* getEquippedHitSourceByFormID(DefeatActorType source, RE::FormID hitSource);
        bool wornHasAnyKeyword(DefeatActorType source, std::list<std::string> kwds);
        bool wornHasAnyKeyword(DefeatActor& source, std::list<std::string> kwds);
        bool hasKeywordString(DefeatActorType source, std::string kwd);
        bool notInFlyingState(DefeatActorType source);
        bool notInFlyingState(DefeatActor& source);
        bool hasSpell(DefeatActorType source, RE::SpellItem* spell);
        bool hasMagicEffect(DefeatActorType source, RE::EffectSetting* effect);
        bool isInKillMove(DefeatActorType source);
        bool isQuestEnabled(RE::TESQuest* quest);
        bool isInCombat(DefeatActorType source);
    };

    struct RawHitEvent {
        RE::TESObjectREFR* target;
        RE::TESObjectREFR* aggressor;
        RE::FormID source;
        RE::FormID projectile;
        bool isPowerAttack = false;
        bool isSneakAttack = false;
        bool isBashAttack = false;
        bool isHitBlocked = false;
    };

    class HitEvent {
    public:
        HitEvent() = default;
        ~HitEvent() = default;
        DefeatActorType target = nullptr;
        DefeatActorType aggressor = nullptr;
        HitSource source;
        HitProjectile projectile;
        bool isPowerAttack = false;
        bool isSneakAttack = false;
        bool isBashAttack = false;
        bool isHitBlocked = false;
    };

    enum HitResult { SKIP, KNONKOUT, STANDING_STRUGGLE, KNONKDOWN };

    using HitEventType = HitEvent;

    class DynamicDefeatDepleter;

    class DefeatCombatManager {
    public:
        struct HitSpamKey {
            RE::FormID actor;
            RE::FormID source;
        };
        struct ProjectileSpamHash {
            std::size_t operator()(const HitSpamKey& k) const {
                return std::hash<std::uint32_t>()(k.actor) ^ (std::hash<std::uint32_t>()(k.source) << 1);
            }
        };

        struct HitSpamEqual {
            bool operator()(const HitSpamKey& lhs, const HitSpamKey& rhs) const {
                return lhs.actor == rhs.actor && lhs.source == rhs.source;
            }
        };

        RE::BSFixedString* OnSLDefeatPlayerKnockDownEventName;

        DefeatCombatManager(IDefeatActorManager* defeatActorManager, IDefeatManager* defeatManager);
        ~DefeatCombatManager();

        IDefeatManager* getDefeatManager() { return _defeatManager; };

        void onActorEnteredToCombatState(RE::Actor* target_actor);
        void onHitHandler(RawHitEvent event);
        HitEventType createHitEvent(RE::Actor* target_actor, RE::Actor* aggr_actor,
                                            RawHitEvent rawHitEvent);

        void calculatePlayerHit(HitEventType event);
        HitResult KDWay(HitEventType event);
        HitResult KDWayWound(HitEventType event);
        HitResult KDWayExhaustion(HitEventType event);
        HitResult KDWayVulnerability(HitEventType event);
        HitResult KDWayDynamic(HitEventType event);
        float KDWayDynamicCalculation(HitEventType event);
        HitResult KDWayPowerAtk(HitEventType event);

        void shedulePlayerDeplateDynamicDefeat();
        std::atomic<bool> _playerDeplateDynamicDefeatStopThread = true;
        void interruptPlayerDeplateDynamicDefeat();

        bool KDOnlyBack(bool opt, HitEventType event);
        bool registerAndCheckHitGuard(RE::TESObjectREFR* actor, RE::FormID source, RE::FormID projectile);


    protected:
        SexLabDefeat::IDefeatActorManager* _defeatActorManager;
        SexLabDefeat::IDefeatManager* _defeatManager;
        //std::unordered_map<HitSpamKey, std::chrono::high_resolution_clock::time_point, ProjectileSpamHash, HitSpamEqual>
        //    projectileSpamGuard;
        std::unordered_map<HitSpamKey, std::chrono::high_resolution_clock::time_point, ProjectileSpamHash, HitSpamEqual>
            hitSpamGuard;
        std::chrono::milliseconds _hitGuardExpiration;
        SpinLock* hitSpamGuardSpinLock;

        void onPlayerHitHandler(RawHitEvent event, SexLabDefeat::DefeatActorType defActor);
    };
    
    class IDefeatManager abstract {
    public:
        enum GameState {
            NONE,
            PRE_LOAD,
            IN_GAME,
        };

        struct {
            bool ZaZ = false;
            bool DeviousFramework = false;
            bool LRGPatch = false;
        } SoftDependency;

        DefeatForms Forms;

        virtual GameState getGameState() = 0;
        virtual void setGameState(GameState state) = 0;
                
        virtual void requestActorExtraData(DefeatActorType target) = 0;

        virtual DefeatWidget* getWidget() = 0;
        virtual DefeatCombatManager* getCombatManager() = 0;
        virtual IDefeatActorManager* getActorManager() = 0;
        virtual DefeatConfig* getConfig() = 0;
    };
}