#ifndef WIDGETSINGLETON_H
#define WIDGETSINGLETON_H

#include <QWidget>
#include <map>

class WidgetSingleton
{
public:
    template <typename WidgetType>
    class Item
    {
    public:
        explicit Item() { }
        ~Item() { WidgetSingleton::Instance().OnDestroy(typeid(WidgetType).hash_code()); }
    };

    ~WidgetSingleton() { }

    template <typename WidgetType, typename... Args>
    static WidgetType* GetWidget(Args&&... args)
    {
        auto& widget_map_ = Instance().widget_map_;
        auto widget_id = typeid(WidgetType).hash_code();
        if (widget_map_.find(widget_id) == widget_map_.end())
        {
            qDebug() << "spawning widget:" << widget_id;
            widget_map_.emplace(widget_id, new WidgetType(std::forward<Args>(args)...));
        }
        return reinterpret_cast<WidgetType*>(widget_map_[widget_id]);
    }

protected:
    WidgetSingleton() { }

    static WidgetSingleton& Instance()
    {
        static WidgetSingleton instance;
        return instance;
    }

    static inline void OnDestroy(size_t widget_id)
    {
        auto& widget_map_ = Instance().widget_map_;
        qDebug() << widget_id << " on destroy";
        widget_map_.erase(widget_id);
    }

    std::map<size_t, QWidget*> widget_map_;
};

#endif // WIDGETSINGLETON_H
