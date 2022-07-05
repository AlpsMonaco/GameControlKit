#ifndef WIDGETKEEPER_H
#define WIDGETKEEPER_H

#include <QWidget>
#include <map>

class WidgetKeeper
{
public:
    using WidgetID = size_t;

    template <typename WidgetType>
    class Widget
    {
    public:
        explicit Widget(WidgetKeeper* widget_keeper)
            : widget_keeper_(widget_keeper) { }
        ~Widget() { widget_keeper_->OnDestroy(typeid(WidgetType).hash_code()); }

    protected:
        WidgetKeeper* widget_keeper_;
    };

    WidgetKeeper() { }
    ~WidgetKeeper() { }

    template <typename WidgetType, typename... Args>
    WidgetType* GetWidget(Args&&... args)
    {
        auto widget_id = typeid(WidgetType).hash_code();
        if (widget_map_.find(widget_id) == widget_map_.end())
        {
            qDebug() << "spawning widget:" << widget_id;
            widget_map_.emplace(widget_id, new WidgetType(std::forward<Args>(args)...));
        }
        return reinterpret_cast<WidgetType*>(widget_map_[widget_id]);
    }

protected:
    inline void OnDestroy(WidgetID widget_id)
    {
        qDebug() << widget_id << " on destroy";
        widget_map_.erase(widget_id);
    }

protected:
    std::map<WidgetID, QWidget*> widget_map_;
};

#endif // WIDGETKEEPER_H
